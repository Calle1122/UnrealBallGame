// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathBox.h"

#include "CharacterBase.h"

// Sets default values
ADeathBox::ADeathBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeathTriggerBox = CreateDefaultSubobject<UBoxComponent>("Death Box");
	SetRootComponent(DeathTriggerBox);

	DeathTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathBox::MyOverlapFunc);
}

// Called when the game starts or when spawned
void ADeathBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathBox::MyOverlapFunc(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(CastChecked<ACharacterBase>(OtherActor))
	{
		ACharacterBase* cBase = CastChecked<ACharacterBase>(OtherActor);

		cBase->StartRespawn();
	}
}

