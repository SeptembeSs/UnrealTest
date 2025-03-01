// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NULLTEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Health")
	float Health = 500.0f;

	UPROPERTY(EditAnywhere,Category="Health")
	float MaxHealth = 500.0f;

	UPROPERTY(EditAnywhere,Category="Health")
	float CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void LoseHealth(float Attacked);

	FORCEINLINE float GetHealthProportion() const { return 500/Health; }

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
};
