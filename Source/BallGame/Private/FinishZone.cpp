// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishZone.h"

#include "CharacterBase.h"

// Sets default values
AFinishZone::AFinishZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FinishZoneMesh = CreateDefaultSubobject<UStaticMeshComponent>("Checkpoint Mesh");
	SetRootComponent(FinishZoneMesh);
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->SetupAttachment(FinishZoneMesh);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishZone::MyOverlapFunc);
}

// Called when the game starts or when spawned
void AFinishZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinishZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishZone::MyOverlapFunc(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(CastChecked<ACharacterBase>(OtherActor))
	{
		ACharacterBase* cBase = CastChecked<ACharacterBase>(OtherActor);
		cBase->FinishLevel();
		TriggerBox->DestroyComponent();
	}
}

