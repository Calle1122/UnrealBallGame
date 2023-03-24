// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UBallGameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

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

void ACharacterBase::HandlePause()
{
	if(PauseHUD->isPaused)
	{
		if(!FinishedLevel)
		{
			PauseHUD->FadeOutPause();
			GameHUD->EnableWidget();
		}
	}
	else
	{
		if(!FinishedLevel)
		{
			GameHUD->DisableWidget();
			PauseHUD->FadeInPause();
		}
	}

	BallInput->WantsToPause=false;
}

void ACharacterBase::FinishLevel()
{
	shouldCount = false;
	FinishedLevel = true;
	
	GameHUD->DisableWidget();

	CanRotateCamera = false;
	
	FinishLevelHUD->TimerText->SetText(GameHUD->TimerText->GetText());
	FinishLevelHUD->SetVisibility(ESlateVisibility::Visible);
	FinishLevelHUD->StartFinishAnimations();

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void ACharacterBase::RestartLevel()
{
	FName LevelName = GetWorld()->GetCurrentLevel()->GetFName();
	UGameplayStatics::OpenLevel(this, LevelName);
}

bool ACharacterBase::GroundCheck()
{
	FVector startLocation = GetActorLocation();
	FVector endLocation = startLocation - FVector(0, 0, 100);

	ECollisionChannel collisionChannel = ECC_WorldStatic;

	FHitResult hitResult;
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, collisionChannel, queryParams)) {
		return true;
	}
	else {
		return false;
	}
}

void ACharacterBase::EnableDashUI()
{
	GameHUD->DashText->SetVisibility(ESlateVisibility::Visible);
}

void ACharacterBase::TriggerDashUI()
{
	GameHUD->FadeInDash();
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

	shouldCount = true;

	PlayerSpawnRotation = BallMesh->GetComponentRotation().Yaw;
	
	DisableMovement();
	GetWorld()->GetTimerManager().SetTimer(EnableMoveTimer, this, &ACharacterBase::EnableMovement, 3.75f, false);
	
	if(BallGameHUDClass)
	{
		GameHUD = CreateWidget<UBallGameHUD>(GetWorld()->GetFirstPlayerController(), BallGameHUDClass);
		GameHUD->AddToPlayerScreen();

		GameHUD->DashText->SetVisibility(ESlateVisibility::Hidden);
		
		GetWorld()->GetTimerManager().SetTimer(DashUIStartDelay, this, &ACharacterBase::EnableDashUI, 3.7f, false);
		
		GameHUD->StartGameUIAnimations();
	}
	
	if(BallGameFinishHUDClass)
	{
		FinishLevelHUD = CreateWidget<UFinishHUD>(GetWorld()->GetFirstPlayerController(), BallGameFinishHUDClass);
		FinishLevelHUD->AddToPlayerScreen();

		FinishLevelHUD->SetVisibility(ESlateVisibility::Hidden);
		
		FinishLevelHUD->RestartLevelButton->OnClicked.AddDynamic(this, &ACharacterBase::RestartLevel);
	}
	if(BallGamePauseClass)
	{
		PauseHUD = CreateWidget<UPauseHUD>(GetWorld()->GetFirstPlayerController(), BallGamePauseClass);
		PauseHUD->AddToPlayerScreen();

		PauseHUD->ResumeButton->OnClicked.AddDynamic(this, &ACharacterBase::HandlePause);
		PauseHUD->RestartButton->OnClicked.AddDynamic(this, &ACharacterBase::RestartLevel);
	}
}

void ACharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(GameHUD)
	{
		GameHUD->RemoveFromParent();
		GameHUD = nullptr;
	}
	if(PauseHUD)
	{
		PauseHUD->RemoveFromParent();
		PauseHUD = nullptr;
	}
	if(FinishLevelHUD)
	{
		FinishLevelHUD->RemoveFromParent();
		FinishLevelHUD = nullptr;
	}
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(shouldCount)
	{
		TotalTime+=DeltaTime;
	}
	
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
			CanRotateCamera=true;
			hasStartedTimer = true;
		}
	}

	if(BallInput->WantsToPause)
	{
		HandlePause();
	}

	canJump = GroundCheck();
	if(canJump)
	{
		TimeInAir = 0;
	}
	else
	{
		TimeInAir+=DeltaTime;
	}
	
	if (BallInput->WantsToJump && TimeSinceLastJump>.5f)
	{
		if(canJump || TimeInAir < CyoteTime)
		{
			BallMovement->Jump(BallMesh);
			TimeSinceLastJump = 0;
		}
	}

	TimeSinceLastJump += DeltaTime;
	BallInput->WantsToJump = false;

	if(BallInput->WantsToDash)
	{
		if(BallMovement->CanDash)
		{
			GameHUD->FadeOutDash();
			GetWorld()->GetTimerManager().SetTimer(FadeInDashTimer, this, &ACharacterBase::TriggerDashUI, 3.0f, false);
		}
		
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
	if(CanRotateCamera)
	{
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
	if(FinishedLevel)
	{
		FRotator NewRot = GetActorRotation();
		NewRot.Yaw+=.25f;
		SetActorRotation(NewRot);

		TimeSinceFinished+=DeltaTime;
		
		BallMovement->MoveSpeed = FMath::Lerp(BallMovement->MoveSpeed, 0, TimeSinceFinished);
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BallInput->SetupInput(Controller, PlayerInputComponent);
}
