// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class NULLTEST_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;
protected:

	UFUNCTION(Blueprintable)
	void OnRestartButtonClicked();

	UFUNCTION(Blueprintable)
	void OnExitButtonClicked();
};
