// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UPauseHUD.generated.h"

/**
 * s
 */
UCLASS(Abstract)
class BALLGAME_API UPauseHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	bool isPaused;
	
	void FadeInPause();
	UFUNCTION()
	void FadeOutPause();
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PauseHeaderText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* BackgroundImage;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResumeButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* BackgroundFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* BackgroundFadeOut;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* HeaderFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* HeaderFadeOut;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* ResumeFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* ResumeFadeOut;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* RestartFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* RestartFadeOut;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* MenuFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* MenuFadeOut;
};
