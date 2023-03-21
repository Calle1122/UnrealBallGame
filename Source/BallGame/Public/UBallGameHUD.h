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
	void FadeInDash();
	void FadeOutDash();

	void EnableWidget();
	void DisableWidget();
	
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
    class UTextBlock* DashText;

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
	
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
    UWidgetAnimation* DashFadeIn;
    UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
    UWidgetAnimation* DashFadeOut;
    UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
    UWidgetAnimation* DashIdle;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* WidgetFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* WidgetFadeOut;
};
