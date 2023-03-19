// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UBallGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ball Mesh");
	SetRootComponent(BallMesh);
	BallMesh->SetSimulatePhysics(true);

	//Movement & Input
	BallInput = CreateDefaultSubobject<UMyInputSystem>("Ball Input");
	BallMovement = CreateDefaultSubobject<UMyMovement>("Ball Movement");

	//Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");

	SpringArm->SetupAttachment(BallMesh);
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//Spring Arm
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-15.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 550.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 4.0f;
}

void ACharacterBase::StartRespawn()
{
	GameHUD->PlayDeathAnimation();
	GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &ACharacterBase::RespawnCharacter, .25f, false);
}

void ACharacterBase::RespawnCharacter()
{
	DisableMovement();
	BallMesh->SetWorldLocation(SpawnPoint);
	SetActorRotation(FRotator(0, PlayerSpawnRotation, 0));
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-15.0f, 0.0f, 0.0f));
	GetWorld()->GetTimerManager().SetTimer(EnableMoveTimer, this, &ACharacterBase::EnableMovement, .75f, false);
}

void ACharacterBase::EnableMovement()
{
	SpringArm->CameraLagSpeed = 4.0f;
	BallMovement->MoveSpeed = 1.0f;
}

void ACharacterBase::DisableMovement()
{
	SpringArm->CameraLagSpeed = 0;
	BallMovement->MoveSpeed = 0;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	DisableMovement();
	GetWorld()->GetTimerManager().SetTimer(EnableMoveTimer, this, &ACharacterBase::EnableMovement, 3.75f, false);
	
	if(BallGameHUDClass)
	{
		GameHUD = CreateWidget<UBallGameHUD>(GetWorld()->GetFirstPlayerController(), BallGameHUDClass);
		GameHUD->AddToPlayerScreen();

		GameHUD->StartGameUIAnimations();
	}
}

void ACharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(GameHUD)
	{
		GameHUD->RemoveFromParent();
		GameHUD = nullptr;
	}
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TotalTime+=DeltaTime;
	int Min = (int)(TotalTime/60);
	int Sec = ((int)TotalTime % 60);
	int MSec = ((int)(TotalTime*1000)%1000);

	if(hasStartedTimer)
	{
		GameHUD->SetTimer(MSec,Sec,Min);
	}
	else
	{
		if(TotalTime>=3.75f)
		{
			TotalTime = 0;
			hasStartedTimer = true;
		}
	}
	
	if (BallInput->WantsToJump)
	{
		BallMovement->Jump(BallMesh);
		BallInput->WantsToJump = false;
	}

	if(BallInput->WantsToDash)
	{
		BallMovement->Dash();
		BallInput->WantsToDash = false;
	}

	BallMovement->Move(BallMesh, BallInput->MoveVector, BallInput->WantsToMove, CameraComp->GetRightVector());
	BallInput->WantsToMove = false;

	if (BallInput->WantsToZoom)
	{
		ZoomFactor += DeltaTime / .5f;
	}
	else
	{
		ZoomFactor -= DeltaTime / .25f;
	}

	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArm->TargetArmLength = FMath::Lerp<float>(550.0f, 400.0f, ZoomFactor);

	//Pitch And Yaw for Camera
	if (BallInput->WantsToMoveCameraY)
	{
		FRotator NewYawRotation = GetActorRotation();
		NewYawRotation.Yaw += BallInput->CameraVector.X;
		SetActorRotation(NewYawRotation);
		BallInput->WantsToMoveCameraY = false;
	}
	else
	{
		BallMesh->SetPhysicsAngularVelocityInDegrees(FVector(0, 0, 0), false);
	}

	if (BallInput->WantsToMoveCameraP)
	{
		FRotator NewPitchRotation = SpringArm->GetComponentRotation();
		NewPitchRotation.Pitch = FMath::Clamp(NewPitchRotation.Pitch + BallInput->CameraVector.Y, -80.0f, -15.0f);
		SpringArm->SetWorldRotation(NewPitchRotation);
		BallInput->WantsToMoveCameraP = false;
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BallInput->SetupInput(Controller, PlayerInputComponent);
}
