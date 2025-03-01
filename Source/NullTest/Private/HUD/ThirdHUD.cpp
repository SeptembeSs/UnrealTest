// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ThirdHUD.h"

#include "HUD/PauseWidget.h"
#include "HUD/UserHealthWidget.h"

void AThirdHUD::CreateHealthWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController != nullptr)
	{
		if (UserHealthWidgetClass != nullptr)
		{
			UserHealthWidget = CreateWidget<UUserHealthWidget>(PlayerController, UserHealthWidgetClass);
			UserHealthWidget->AddToViewport();
		}
		
	}
}

void AThirdHUD::SetAllScoreBoxNum(int Num)
{
	if (UserHealthWidget != nullptr)
		UserHealthWidget->UpdateTotalScore(Num);
}

void AThirdHUD::UpdateHealthWidget(float MaxHealth, float CurrentHealth)
{
	if (UserHealthWidget != nullptr)
	{
		UserHealthWidget->UpdateHealthBar(MaxHealth, CurrentHealth);
	}
}

void AThirdHUD::UpdateHealthScoreWidget(int Score)
{
	if (UserHealthWidget != nullptr)
		UserHealthWidget->UpdateScore(Score);
}
