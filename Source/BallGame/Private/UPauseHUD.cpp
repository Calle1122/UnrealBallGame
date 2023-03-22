// Fill out your copyright notice in the Description page of Project Settings.


#include "UPauseHUD.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPauseHUD::FadeInPause()
{
	PlayAnimation(BackgroundFadeIn,0);
	PlayAnimation(HeaderFadeIn, .075f);
	PlayAnimation(ResumeFadeIn, .1f);
	PlayAnimation(RestartFadeIn, .125f);
	PlayAnimation(MenuFadeIn, .15f);
	
	GetWorld()->GetFirstPlayerController()->Pause();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	isPaused = true;
}

void UPauseHUD::FadeOutPause()
{
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	GetWorld()->GetFirstPlayerController()->Pause();

	isPaused = false;
	
	PlayAnimation(BackgroundFadeOut,.15f);
	PlayAnimation(HeaderFadeOut, .045f);
	PlayAnimation(ResumeFadeOut, .03f);
	PlayAnimation(RestartFadeOut, .015f);
	PlayAnimation(MenuFadeOut, 0);
}
