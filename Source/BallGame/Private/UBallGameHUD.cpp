// Fill out your copyright notice in the Description page of Project Settings.


#include "UBallGameHUD.h"
#include "Components/TextBlock.h"

void UBallGameHUD::SetTimer(int MSec, int Sec, int Min)
{
	if(TimerText)
	{
		FString sMin, sSec, sMSec;
	
		if(Min<10)
		{
			sMin = "0" + FString::FromInt(Min);	
		}
		else
		{
			sMin = FString::FromInt(Min);
		}

		if(Sec<10)
		{
			sSec = "0" + FString::FromInt(Sec);
		}
		else
		{
			sSec = FString::FromInt(Sec);
		}

		if(MSec<10)
		{
			sMSec = "00" + FString::FromInt(MSec);
		}
		else if(MSec>9 && MSec<100)
		{
			sMSec = "0" + FString::FromInt(MSec);
		}
		else
		{
			sMSec = FString::FromInt(MSec);
		}
	
		FString stringFullTime = sMin + ":" + sSec + ":" + sMSec;
	
		TimerText->SetText(FText::FromString(stringFullTime));
	}
}

void UBallGameHUD::StartGameUIAnimations()
{
	UBallGameHUD::PlayAnimation(StartCountDown3, 0);
	UBallGameHUD::PlayAnimation(StartCountDown2, 0);
	UBallGameHUD::PlayAnimation(StartCountDown1, 0);
	UBallGameHUD::PlayAnimation(StartCountDownGO, 0);
	UBallGameHUD::PlayAnimation(RevealTimer, 0);
	PlayAnimation(DashFadeIn, 3.75f);
}

void UBallGameHUD::PlayDeathAnimation()
{
	PlayAnimation(DeathImageSlide, 0);
}

void UBallGameHUD::FadeInDash()
{
	PlayAnimation(DashFadeIn, 0);
	PlayAnimation(DashIdle, .40f, 0);
}

void UBallGameHUD::FadeOutDash()
{
	PlayAnimation(DashFadeOut, 0);
}

void UBallGameHUD::EnableWidget()
{
	PlayAnimation(WidgetFadeIn, 0);
}

void UBallGameHUD::DisableWidget()
{
	PlayAnimation(WidgetFadeOut, 0);
}
