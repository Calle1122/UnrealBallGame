// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"

#include "CharacterBase.h"
#include "GameFramework/Character.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckPointMesh = CreateDefaultSubobject<UStaticMeshComponent>("Checkpoint Mesh");
	SetRootComponent(CheckPointMesh);

	MiddleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Middle Mesh");
	MiddleMesh->SetupAttachment(CheckPointMesh);
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->SetupAttachment(CheckPointMesh);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::MyOverlapFunc);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckPoint::MyOverlapFunc(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(CastChecked<ACharacterBase>(OtherActor))
	{
		ACharacterBase* cBase = CastChecked<ACharacterBase>(OtherActor);

		FVector triggerLocation = TriggerBox->GetComponentTransform().GetLocation();
		cBase->SpawnPoint = FVector(triggerLocation.X, triggerLocation.Y, triggerLocation.Z + 100);
		cBase->PlayerSpawnRotation = SpawnRotation;

		MiddleMesh->SetMaterial(0, CheckpointUnlockedMat);
		
		TriggerBox->DestroyComponent();
	}
}

