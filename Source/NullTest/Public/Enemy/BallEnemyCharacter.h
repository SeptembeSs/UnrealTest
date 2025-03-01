// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseEnemyCharacter.h"
#include "BallEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NULLTEST_API ABallEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABallProjecttile> BallProjecttileClass;
	
	FTimerHandle BallProjectileTimerHandle;

	//delay time
	float BallInterval = 1.5f;
	float BallDelay = 0.5f;

	void CreateBallProjectile();

	virtual void RefreshSeeActor() override;
};
