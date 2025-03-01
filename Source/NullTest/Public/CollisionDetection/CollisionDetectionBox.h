// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollisionDetectionBox.generated.h"

UCLASS()
class NULLTEST_API ACollisionDetectionBox : public AActor
{
	GENERATED_BODY()

public:
	
	// Sets default values for this pawn's properties
	ACollisionDetectionBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void InitStatus();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	bool IsMaterialsChanged;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Mesh")
	TObjectPtr<UMaterialInterface> CollisionAfterMaterial;

	FTimerHandle BoxMoveTimerHandle;
	void ChangeDistance();
	void MoveControl();
	UFUNCTION()
	void DelayChangeFlag();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Move")
	float MoveTime = 3.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Move")
	bool MoveDistance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Move")
	float MoveSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Move")
	FVector MoveVector;
	
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE float GetMoveSpeed() const { return MoveSpeed; };
	FORCEINLINE void ChangeMoveSpeed(const float Value) { MoveSpeed = Value; };

	FORCEINLINE FVector GetMoveVector() const { return MoveVector; };
	FORCEINLINE void ChangeMoveVector(const FVector& Value) { MoveVector = Value; };
	
	
};
