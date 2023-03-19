// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UBallGameHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class BALLGAME_API UBallGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetTimer(int MSec, int Sec, int Min);
	void StartGameUIAnimations();
	void PlayDeathAnimation();
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TimerText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CountDownText3;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CountDownText2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CountDownText1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CountDownTextGO;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* DeathImage;
	
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* RevealTimer;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* StartCountDown3;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* StartCountDown2;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* StartCountDown1;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* StartCountDownGO;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* DeathImageSlide;
};
