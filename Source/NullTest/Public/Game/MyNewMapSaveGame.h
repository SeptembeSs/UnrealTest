// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyNewMapSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NULLTEST_API UMyNewMapSaveGame : public USaveGame
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,Category="Others")
	TMap<FString,FVector> MyVectorDataMap;
	
	UPROPERTY(EditAnywhere,Category="Player")
	FVector PlayerVector;
	
	UPROPERTY(EditAnywhere,Category="Player")
	int PlayerScore;
	
	UPROPERTY(EditAnywhere,Category="Player")
	float PlayerCurrentHealth;
	
	UPROPERTY(EditAnywhere,Category="Player")
	float PlayerMaxHealth;

public:
	FORCEINLINE void SetPlayerVector(FVector Vector) { PlayerVector = Vector; }
	FORCEINLINE FVector GetPlayerVector() { return PlayerVector; }
	
	FORCEINLINE void SetPlayerScore(int Value) { PlayerScore = Value; }
	FORCEINLINE int GetPlayerScore() { return PlayerScore; }
	
	FORCEINLINE void SetPlayerCurrentHealth(float Value) { PlayerCurrentHealth = Value; }
	FORCEINLINE float GetPlayerCurrentHealth() { return PlayerCurrentHealth; }
	
	FORCEINLINE void SetPlayerMaxHealth(float Value) { PlayerMaxHealth = Value; }
	FORCEINLINE float GetPlayerMaxHealth() { return PlayerMaxHealth; }
	
};
