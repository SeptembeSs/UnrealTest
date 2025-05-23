// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ACPPPlayerController.h"

#include "CollisionDetection/ScoreBox.h"
#include "Components/InputComponent.h"
#include "HUD/PauseWidget.h"
#include "HUD/RestartWidget.h"
#include "HUD/ThirdHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerCharacter.h"

void AACPPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitViewport();

	
}

void AACPPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		InPawn->SetActorLocation(FVector(0, 0, 0));
	}
}



void AACPPPlayerController::InitViewport()
{
	// if (HealthWidgetClass != nullptr)
	// {
	// 	UserHealthWidget = CreateWidget<UUserHealthWidget>(this, HealthWidgetClass);
	// 	UserHealthWidget->AddToViewport();
	// }
	ThirdHUD = Cast<AThirdHUD>(GetHUD());
	if (ThirdHUD != nullptr)
	{
		ThirdHUD->CreateHealthWidget();

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScoreBox::StaticClass(), FoundActors);
		ThirdHUD->SetAllScoreBoxNum(FoundActors.Num());
	}
}

void AACPPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//bind key P
	InputComponent->BindKey(EKeys::P, IE_Pressed, this, &AACPPPlayerController::ShowPauseWidget);

	// InputComponent->BindKey(EKeys::N, IE_Pressed, this, &AACPPPlayerController::SaveGame);
	// InputComponent->BindKey(EKeys::M, IE_Pressed, this, &AACPPPlayerController::LoadGame);
}

void AACPPPlayerController::PauseGameToUI()
{
	SetPause(true);
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}

void AACPPPlayerController::ResumeGameFromUI()
{
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AACPPPlayerController::ShowRestartWidget()
{
	if (RestartWidgetClass != nullptr)
	{
		
		PauseGameToUI();
		
		RestartWidget = CreateWidget<URestartWidget>(this, RestartWidgetClass);
		RestartWidget->AddToViewport();
	}
}

void AACPPPlayerController::HideRestartWidget()
{
	if (RestartWidget != nullptr)
	{
		RestartWidget->RemoveFromParent();
		RestartWidget->Destruct();

		ResumeGameFromUI();
	}
}

void AACPPPlayerController::ShowPauseWidget()
{
	if (PauseWidgetClass != nullptr)
	{
		PauseGameToUI();

		PauseWidget = CreateWidget<UPauseWidget>(this, PauseWidgetClass);
		PauseWidget->AddToViewport();
	}
}

void AACPPPlayerController::HidePauseWidget()
{
	if (PauseWidget != nullptr)
	{
		PauseWidget->RemoveFromParent();
		PauseWidget->Destruct();

		ResumeGameFromUI();
	}
}

void AACPPPlayerController::UpdateHealthBar(float MaxHealth, float CurrentHealth)
{
	// if (UserHealthWidget != nullptr)
	// {
	// 	UserHealthWidget->UpdateHealthBar(MaxHealth, CurrentHealth);
	// }
	UE_LOG(LogTemp, Warning, TEXT("player UpdateHealthBar"));
	if (ThirdHUD != nullptr)
		ThirdHUD->UpdateHealthWidget(MaxHealth, CurrentHealth);
}

void AACPPPlayerController::UpdateScore(int Score)
{
	if (ThirdHUD != nullptr)
		ThirdHUD->UpdateHealthScoreWidget(Score);
}

void AACPPPlayerController::LoadGame()
{
	SaveOrLoadGame(false);
}

void AACPPPlayerController::SaveGame()
{
	SaveOrLoadGame(true);
}

void AACPPPlayerController::SaveOrLoadGame(bool IsSave)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayerCharacter::StaticClass(), FoundActors);
	if (FoundActors.Num() == 1)
	{
		AMyPlayerCharacter* PlayerCharacter = Cast<AMyPlayerCharacter>(FoundActors[0]);
		if (PlayerCharacter)
		{
			if (IsSave)
			{
				PlayerCharacter->PlayerSaveGame();
			}
			else
			{
				PlayerCharacter->PlayerLoadGame();
			}
			
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player numder error"));
	}
}
