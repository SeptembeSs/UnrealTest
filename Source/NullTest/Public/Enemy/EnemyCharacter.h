// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HealthInterface.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;
class ABallProjecttile;
class ULookComponent;

UCLASS()
class NULLTEST_API AEnemyCharacter : public ACharacter,public IHealthInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> TargetCharacter;

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<FHitResult> TArrayResult;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABallProjecttile> BallProjecttileClass;

	bool bCanSeeTargetCharacter;

	bool bPerviousCanSeeTargetCharacter;

	FTimerHandle BallProjectileTimerHandle;

	//delay time
	float BallInterval = 1.5f;
	float BallDelay = 0.5f;

	void CreateBallProjectile();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Component")
	TObjectPtr<UHealthComponent> HealthComponent;
	
public:	
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

	void OnDeath_Implementation() override;

	void OnDamage_Implementation() override;

};




