// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallProjecttile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class NULLTEST_API ABallProjecttile : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	
	void OnBallProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Sets default values for this actor's properties
	ABallProjecttile();

	UPROPERTY(EditAnywhere,Category = "Create")
	TObjectPtr<USoundBase> CreateSoundBase;
	
	UPROPERTY(EditAnywhere,Category = "Damage")
	TObjectPtr<USoundBase> HitSoundBase;

	UPROPERTY(EditAnywhere,Category = "Damage")
	TObjectPtr<USoundAttenuation> HitSoundAttenuation;

	UPROPERTY(EditAnywhere,Category = "Damage")
	TObjectPtr<UParticleSystem> HitParticles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category = "Damage")
	float Damage = 10.f;
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="Ball",meta=(AllowPrivateAccess=true))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="Ball",meta=(AllowPrivateAccess=true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UProjectileMovementComponent* GetMovementComponent() const { return ProjectileMovementComponent; }



};
