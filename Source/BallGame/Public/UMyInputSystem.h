// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <InputMappingContext.h>
#include <Windows.ApplicationModel.Activation.h>

#include "EnhancedInput/Public/InputActionValue.h"
#include "UMyInputSystem.Generated.h"

/**
 * 
 */
UCLASS()
class BALLGAME_API UMyInputSystem : public UInputComponent
{
	GENERATED_BODY()
public:
	UMyInputSystem();

	//Input Context
	UPROPERTY(EditAnywhere, Category="InputContext")
	TObjectPtr<UInputMappingContext> BallMovementContext;

	//Movement Actions
	UPROPERTY(EditAnywhere, Category="Inputs")
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, Category="Inputs")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Inputs")
	TObjectPtr<UInputAction> DashAction;

	//Camera Actions
	UPROPERTY(EditAnywhere, Category="Camera Inputs")
	TObjectPtr<UInputAction> ZoomInAction;
	UPROPERTY(EditAnywhere, Category="Camera Inputs")
	TObjectPtr<UInputAction> ZoomOutAction;
	UPROPERTY(EditAnywhere, Category="Camera Inputs")
	TObjectPtr<UInputAction> CameraPitchAction;
	UPROPERTY(EditAnywhere, Category="Camera Inputs")
	TObjectPtr<UInputAction> CameraYawAction;

	UPROPERTY(EditAnywhere, Category="Pause Inputs")
	TObjectPtr<UInputAction> PauseGameAction;

	bool WantsToJump;
	bool WantsToMove;
	bool WantsToDash;

	bool WantsToMoveCameraP;
	bool WantsToMoveCameraY;
	bool WantsToZoom;

	bool WantsToPause;
	
	FVector2D MoveVector;

	FVector2D CameraVector;
	
	void SetupInput(TObjectPtr<AController> Controller, UInputComponent* PlayerInputComponent);

	void BallMove(const FInputActionValue& Value);
	void BallJump(const FInputActionValue& Value);
	void BallDash(const FInputActionValue& Value);

	void ZoomCamera(const FInputActionValue& Value);
	void ZoomOutCamera(const FInputActionValue& Value);
	void MoveCameraPitch(const FInputActionValue& Value);
	void MoveCameraYaw(const FInputActionValue& Value);

	void BallGamePause(const FInputActionValue& Value);

private:
	APlayerController* PlayerController;
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedSubsystem;
};


