// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBox.generated.h"

class UBoxComponent;

UCLASS()
class NULLTEST_API AScoreBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreBox();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void InitComponents();
	
	void MoveControl(float DeltaTime);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,category="Mesh")
	TObjectPtr<UBoxComponent> BoxMesh;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
