// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseEnemyCharacter.h"
#include "RunEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NULLTEST_API ARunEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement",meta=(AllowPrivateAccess=true))
	float RunSpeed;

protected:
	virtual void InitComponents() override;
	
	virtual void RefreshSeeActor() override;
};
