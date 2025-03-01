// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HealthInterface.h"
#include "BaseEnemyCharacter.generated.h"

class UHealthComponent;
class ABallProjecttile;
class ULookComponent;

UCLASS()
class NULLTEST_API ABaseEnemyCharacter : public ACharacter,public IHealthInterface
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	ABaseEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitComponents();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Component")
	TObjectPtr<UHealthComponent> HealthComponent;

	bool bCanSeeTargetCharacter;

	bool bPerviousCanSeeTargetCharacter;

	virtual void RefreshSeeActor();

public:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> TargetCharacter;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULookComponent> LookComponent;

	// bool LineTraceActor(const AActor* TargetActor);
	//
	// bool CanSeeActor(const AActor* TargetActor, FVector StartVector,FVector EndVector);

	UPROPERTY(visibleAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UFUNCTION()
	void PrintGameModeAndController();

	void OnDeath_Implementation() override;

	void OnDamage_Implementation() override;

};



