// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NULLTEST_API IHealthInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//death
	UFUNCTION(blueprintNativeEvent, Category = "Health")
	void OnDeath();
	virtual void OnDeath_Implementation() = 0;  //纯虚函数

	//Damage
	UFUNCTION(blueprintNativeEvent, Category = "Health")
	void OnDamage();
	virtual void OnDamage_Implementation() = 0;
};
