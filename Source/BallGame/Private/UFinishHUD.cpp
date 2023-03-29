// Fill out your copyright notice in the Description page of Project Settings.


#include "UFinishHUD.h"
#include "Components/TextBlock.h"

void UFinishHUD::StartFinishAnimations()
{
	PlayAnimation(BackImageFadeIn, 0);
	PlayAnimation(FinishTextFadeIn, 0);
	PlayAnimation(TimeTextFadeIn, 0);
	PlayAnimation(TimerTextFadeIn, 0);
	PlayAnimation(BestTimeTextFadeIn, 0);
	PlayAnimation(BestTimerTextFadeIn, 0);

	PlayAnimation(RestartButtonFadeIn, 0);
	PlayAnimation(NextLevelButtonFadeIn, 0);
	PlayAnimation(MainMenuButtonFadeIn, 0);
}
