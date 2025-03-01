// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ThirdHUD.generated.h"

class UPauseWidget;
class UUserHealthWidget;
/**
 * 
 */
UCLASS()
class NULLTEST_API AThirdHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,Category="HUD")
	TSubclassOf<UUserHealthWidget> UserHealthWidgetClass;

public:
	UFUNCTION()
	void CreateHealthWidget();

	UFUNCTION()
	void SetAllScoreBoxNum(int Num);
	
	UFUNCTION()
	void UpdateHealthWidget(float MaxHealth,float CurrentHealth);

	UFUNCTION()
	void UpdateHealthScoreWidget(int Score);
	
private:
	UPROPERTY()
	TObjectPtr<UUserHealthWidget> UserHealthWidget;
	
	
};
