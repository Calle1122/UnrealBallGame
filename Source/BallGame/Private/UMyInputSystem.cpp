// Fill out your copyright notice in the Description page of Project Settings.

#include "UMyInputSystem.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInput/Public/InputActionValue.h"

UMyInputSystem::UMyInputSystem()
{
	
}

void UMyInputSystem::SetupInput(TObjectPtr<AController> Controller, UInputComponent* PlayerInputComponent)
{
	if(PlayerController==nullptr)PlayerController = CastChecked<APlayerController>(Controller);

	if(EnhancedSubsystem==nullptr)
	{
		EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	}

	if(PlayerController!=nullptr)
	{
		EnhancedSubsystem->AddMappingContext(BallMovementContext, 5);
	}

	UEnhancedInputComponent* EInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if(EInputComponent==nullptr)
	{
		return;
	}

	EInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &UMyInputSystem::BallJump);
	EInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UMyInputSystem::BallMove);
	EInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &UMyInputSystem::BallDash);

	//Camera Input Binding
	EInputComponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &UMyInputSystem::ZoomCamera);
	EInputComponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &UMyInputSystem::ZoomOutCamera);

	EInputComponent->BindAction(CameraPitchAction, ETriggerEvent::Triggered, this, &UMyInputSystem::MoveCameraPitch);
	EInputComponent->BindAction(CameraYawAction, ETriggerEvent::Triggered, this, &UMyInputSystem::MoveCameraYaw);

	EInputComponent->BindAction(PauseGameAction, ETriggerEvent::Triggered, this, &UMyInputSystem::BallGamePause);
}

void UMyInputSystem::BallMove(const FInputActionValue& Value)
{
	WantsToMove = true;
	MoveVector = Value.Get<FVector2D>();
}

void UMyInputSystem::BallJump(const FInputActionValue& Value)
{
	WantsToJump = true;
}

void UMyInputSystem::BallDash(const FInputActionValue& Value)
{
	WantsToDash = true;
}

void UMyInputSystem::ZoomCamera(const FInputActionValue& Value)
{
	WantsToZoom = true;
}

void UMyInputSystem::ZoomOutCamera(const FInputActionValue& Value)
{
	WantsToZoom = false;
}

void UMyInputSystem::MoveCameraPitch(const FInputActionValue& Value)
{
	WantsToMoveCameraP = true;
	CameraVector.Y = Value.Get<float>();
}

void UMyInputSystem::MoveCameraYaw(const FInputActionValue& Value)
{
	WantsToMoveCameraY = true;
	CameraVector.X = Value.Get<float>();
}

void UMyInputSystem::BallGamePause(const FInputActionValue& Value)
{
	WantsToPause = true;
}
