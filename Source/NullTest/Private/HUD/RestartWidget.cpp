// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RestartWidget.h"

#include "Components/Button.h"
#include "Game/ACPPPlayerController.h"
#include "Kismet/GameplayStatics.h"

void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton != nullptr)
	{
		RestartButton->OnClicked.AddDynamic(this,&URestartWidget::OnRestartButtonClicked);
	}

	if (ExitButton != nullptr)
	{
		ExitButton->OnClicked.AddDynamic(this,&URestartWidget::OnExitButtonClicked);
	}
}

void URestartWidget::OnRestartButtonClicked()
{
	AACPPPlayerController* PlayerController = Cast<AACPPPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		//hide
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this,FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartWidget::OnExitButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("quit game"));
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,true);
}
