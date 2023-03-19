// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMyMovement.Generated.h"

/**
 * 
 */
UCLASS()
class BALLGAME_API UMyMovement : public UActorComponent
{
	GENERATED_BODY()
public:
	UMyMovement();

	void Jump(UStaticMeshComponent* TargetMesh);
	void Move(UStaticMeshComponent* TargetMesh, FVector2D MoveDir, bool WantsToMove, FVector CamVector);
	void Dash();
	void UnDash();
	void RefreshDash();

	FTimerHandle DashTimer;
	FTimerHandle DashCooldownTimer;
	bool CanDash;
	
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, Category="Movement")
	float JumpForce;
	UPROPERTY(EditAnywhere, Category="Movement")
	float DashForce;
};
