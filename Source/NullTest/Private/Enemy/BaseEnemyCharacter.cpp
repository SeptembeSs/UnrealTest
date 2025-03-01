// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseEnemyCharacter.h"

#include "Component/HealthComponent.h"
#include "Component/LookComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitComponents();
}

void ABaseEnemyCharacter::InitComponents()
{
	SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
	FTransform Transform = SkeletalMeshComponent->GetSocketTransform("head");

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(SkeletalMeshComponent);
	SceneComponent->SetRelativeLocation(Transform.GetTranslation());
	// UE_LOG(LogTemp, Warning, TEXT("Transform %s"),*Transform.ToString());
	
	LookComponent = CreateDefaultSubobject<ULookComponent>(TEXT("LookComponent"));
	LookComponent->SetupAttachment(SceneComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	TargetCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	LookComponent->SetTargetActor(TargetCharacter);
}



// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RefreshSeeActor();

}

void ABaseEnemyCharacter::RefreshSeeActor()
{
	bCanSeeTargetCharacter = LookComponent->CanSeeActor();

	bPerviousCanSeeTargetCharacter = bCanSeeTargetCharacter;
}

// Called to bind functionality to input
void ABaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemyCharacter::OnDeath_Implementation()
{
	Destroy();
}

void ABaseEnemyCharacter::OnDamage_Implementation()
{
}

void ABaseEnemyCharacter::PrintGameModeAndController()
{
	// 获取当前的世界
	UWorld* World = GetWorld();
	if (World)
	{
		// 获取 GameMode
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
		if (GameMode)
		{
			UE_LOG(LogTemp, Warning, TEXT("Current GameMode: %s"), *GameMode->GetName());
		}

		// 获取 PlayerController
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("Current PlayerController: %s"), *PlayerController->GetName());
		}
	}
}
