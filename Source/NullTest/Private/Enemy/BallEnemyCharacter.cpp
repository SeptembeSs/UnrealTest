// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BallEnemyCharacter.h"

#include "Component/LookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile/BallProjecttile.h"

void ABallEnemyCharacter::CreateBallProjectile()
{
	if (BallProjecttileClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BallProjecttileClass is null"));
		return;
	}

	FVector Forword = GetActorForwardVector();
	FVector Location = GetActorLocation() + Forword * 40.f;
	
	// GetWorld()->SpawnActor<ABallProjecttile>(BallProjecttileClass, Location, GetActorRotation());
	
	FTransform SpawnTransform(GetActorRotation(),Location);
	ABallProjecttile* Projecttile = GetWorld()->SpawnActorDeferred<ABallProjecttile>(BallProjecttileClass,SpawnTransform);

	Projecttile->GetMovementComponent()->InitialSpeed = 7000.f;
	Projecttile->FinishSpawning(SpawnTransform);
}

void ABallEnemyCharacter::RefreshSeeActor()
{
	bCanSeeTargetCharacter = LookComponent->CanSeeActor();
	//即时生成
	// if (bCanSeeTargetCharacter)
	// {
	// 	// UE_LOG(LogTemp, Warning, TEXT("CanSeeTargetCharacter"));
	// 	CreateBallProjectile();
	// }

	//延时生成
	if (bCanSeeTargetCharacter != bPerviousCanSeeTargetCharacter)
	{
		if (bCanSeeTargetCharacter)
		{
			GetWorldTimerManager().SetTimer(BallProjectileTimerHandle,this,&ABallEnemyCharacter::CreateBallProjectile,BallInterval,true,BallDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(BallProjectileTimerHandle);
		}
	}
	bPerviousCanSeeTargetCharacter = bCanSeeTargetCharacter;
}
