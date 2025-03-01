// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/UserHealthWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UUserHealthWidget::UpdateHealthBar(float MaxHealth, float CurrentHealth)
{
	float percentage = (CurrentHealth / MaxHealth) ;
	HealthBar->SetPercent(percentage);
	FString Result = FString::SanitizeFloat(CurrentHealth) + TEXT(" / ") + FString::SanitizeFloat(MaxHealth);
	HealthTextBlock->SetText(FText::FromString(Result));
}

void UUserHealthWidget::UpdateScore(int Score)
{
	FString ScoreString = TEXT(" Socre : ") + FString::FromInt(Score);
	ScoreText->SetText(FText::FromString(ScoreString));
}

void UUserHealthWidget::UpdateTotalScore(int TotalScore)
{
	FString TotalScoreString = TEXT("/ ") + FString::FromInt(TotalScore);
	TotalScoreText->SetText(FText::FromString(TotalScoreString));
}
