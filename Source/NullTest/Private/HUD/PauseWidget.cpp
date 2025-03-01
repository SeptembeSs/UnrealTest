// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PauseWidget.h"

#include "Components/Button.h"
#include "Game/ACPPPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ContinueButton != nullptr)
	{
		ContinueButton->OnClicked.AddDynamic(this,&UPauseWidget::OnContinueButtonClicked);
	}

	if (QuitButton != nullptr)
	{
		QuitButton->OnClicked.AddDynamic(this,&UPauseWidget::OnQuitButtonClicked);
	}
}

void UPauseWidget::OnContinueButtonClicked()
{
	AACPPPlayerController* PlayerController = Cast<AACPPPlayerController>(GetOwningPlayer());
	if (PlayerController != nullptr)
	{
		PlayerController->HidePauseWidget();
	}
}

void UPauseWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,true);
}
