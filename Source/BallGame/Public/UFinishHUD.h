// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UFinishHUD.generated.h"
/**
 * 
 */
UCLASS(Abstract)
class BALLGAME_API UFinishHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	void StartFinishAnimations();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* BackImage;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* FinishText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TimeText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TimerText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* BestTimeText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* BestTimerText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartLevelButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* NextLevelButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* BackImageFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* FinishTextFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* TimeTextFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* TimerTextFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* BestTimeTextFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* BestTimerTextFadeIn;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* RestartButtonFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* NextLevelButtonFadeIn;
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* MainMenuButtonFadeIn;
};
