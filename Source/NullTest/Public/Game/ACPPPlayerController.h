// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ACPPPlayerController.generated.h"

class UPauseWidget;
class AThirdHUD;
class UUserHealthWidget;
class URestartWidget;
/**
 * 
 */
UCLASS()
class NULLTEST_API AACPPPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void InitViewport();

	virtual void SetupInputComponent() override;

public:
	virtual void OnPossess(APawn* InPawn) override;

	void PauseGameToUI();

	void ResumeGameFromUI();

	UPROPERTY(EditDefaultsOnly,Category = "Widget")
	TSubclassOf<URestartWidget> RestartWidgetClass;

	UFUNCTION()
	void ShowRestartWidget();

	UFUNCTION()
	void HideRestartWidget();

	UPROPERTY(EditDefaultsOnly,Category = "Widget")
	TSubclassOf<UPauseWidget> PauseWidgetClass;

	UFUNCTION()
	void ShowPauseWidget();

	UFUNCTION()
	void HidePauseWidget();

	UPROPERTY(EditDefaultsOnly,Category = "Widget")
	TSubclassOf<UUserHealthWidget> HealthWidgetClass;

	UFUNCTION()
	void UpdateHealthBar(float MaxHealth,float CurrentHealth);

	UFUNCTION()
	void UpdateScore(int Score);

	// UFUNCTION()
	// void LoadGame();
	//
	// UFUNCTION()
	// void SaveGame();
	//
	// UFUNCTION()
	// void SaveOrLoadGame(bool IsSave);

private:
	UPROPERTY()
	TObjectPtr<URestartWidget> RestartWidget;

	UPROPERTY()
	TObjectPtr<UPauseWidget> PauseWidget;

	UPROPERTY()
	TObjectPtr<UUserHealthWidget> UserHealthWidget;

	UPROPERTY()
	TObjectPtr<AThirdHUD> ThirdHUD;
};


