// Fill out your copyright notice in the Description page of Project Settings.


#include "UMyMovement.h"

#include "BallGame/BallGame.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

UMyMovement::UMyMovement() : MoveSpeed(10), JumpForce(30), DashForce(3), CanDash(true)
{
}

void UMyMovement::Jump(UStaticMeshComponent* TargetMesh)
{
	TargetMesh->AddImpulse(FVector(0, 0, JumpForce * Physics::ForceMultiplier));
}

void UMyMovement::Dash()
{
	if (CanDash)
	{
		CanDash = false;

		MoveSpeed *= DashForce;
		GetWorld()->GetTimerManager().SetTimer(DashTimer, this, &UMyMovement::UnDash, .1f, false);
		GetWorld()->GetTimerManager().SetTimer(DashCooldownTimer, this, &UMyMovement::RefreshDash, 3.0f, false);
	}
}

void UMyMovement::UnDash()
{
	MoveSpeed /= DashForce;
	GetWorld()->GetTimerManager().ClearTimer(DashTimer);
}

void UMyMovement::RefreshDash()
{
	CanDash = true;
	GetWorld()->GetTimerManager().ClearTimer(DashCooldownTimer);
}


void UMyMovement::Move(UStaticMeshComponent* TargetMesh, FVector2D MoveDir, bool WantsToMove, FVector CamVector)
{
	FVector CurrentVelocity = TargetMesh->GetPhysicsLinearVelocity();

	if (!WantsToMove)
	{
		TargetMesh->SetPhysicsLinearVelocity(FVector(0, 0, CurrentVelocity.Z));
		return;
	}

	FVector2D DesiredMoveDir = MoveDir * (MoveSpeed * Physics::ForceMultiplier);

	FVector rightVel = CamVector * DesiredMoveDir.X;
	FVector forwardVel = TargetMesh->GetForwardVector() * DesiredMoveDir.Y;

	FVector finalMoveDir = forwardVel + rightVel + FVector(0, 0, CurrentVelocity.Z);

	TargetMesh->SetPhysicsLinearVelocity(finalMoveDir);
}
