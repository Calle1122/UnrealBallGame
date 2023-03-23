// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UBallGameHUD.h"
#include "UMyInputSystem.h"
#include "UMyMovement.h"
#include "UPauseHUD.h"
#include "UFinishHUD.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterBase.generated.h"

class UFinishHUD;
UCLASS()
class BALLGAME_API ACharacterBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterBase();
	UPROPERTY(EditAnywhere, Category="BallMesh Root")
	UStaticMeshComponent* BallMesh;
	UPROPERTY(EditAnywhere, Category="Input")
	UMyInputSystem* BallInput;
	UPROPERTY(EditAnywhere, Category="Movement")
	UMyMovement* BallMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn Point")
	FVector SpawnPoint;

	UPROPERTY(EditAnywhere, Category="Widget UI")
	TSubclassOf<UBallGameHUD> BallGameHUDClass;
	UPROPERTY()
	class UBallGameHUD* GameHUD;

	UPROPERTY(EditAnywhere, Category="Widget UI")
	TSubclassOf<UPauseHUD> BallGamePauseClass;
	UPROPERTY()
	class UPauseHUD* PauseHUD;

	UPROPERTY(EditAnywhere, Category="Widget UI")
	TSubclassOf<UFinishHUD> BallGameFinishHUDClass;
	UPROPERTY()
	class UFinishHUD* FinishLevelHUD;

	UFUNCTION()
	void HandlePause();

	void FinishLevel();

	bool CanRotateCamera;
	
	bool shouldCount;
	float TotalTime;

	bool FinishedLevel;
	float TimeSinceFinished;

	bool GroundCheck();
	bool canJump;
	float TimeSinceLastJump;
	float TimeInAir;

	FTimerHandle DashUIStartDelay;
	void EnableDashUI();

	UPROPERTY(EditAnywhere, Category="Cyote Time")
	float CyoteTime;

	FTimerHandle FadeInDashTimer;
	void TriggerDashUI();

	void StartRespawn();
	float PlayerSpawnRotation;
	FTimerHandle RespawnTimer;
	void RespawnCharacter();

	void EnableMovement();
	FTimerHandle EnableMoveTimer;
	void DisableMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//Camera
	UPROPERTY(EditAnywhere, Category="Spring Arm")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category="Camera")
	UCameraComponent* CameraComp;

	float ZoomFactor;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool hasStartedTimer;
};
