// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FinishZone.generated.h"

UCLASS()
class BALLGAME_API AFinishZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishZone();
	UPROPERTY(EditAnywhere, Category="Finish Root")
	UStaticMeshComponent* FinishZoneMesh;
	UPROPERTY(EditAnywhere, Category="Trigger Box")
	UBoxComponent* TriggerBox;

	void OnPlayerCollision(AActor* actor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void MyOverlapFunc(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
