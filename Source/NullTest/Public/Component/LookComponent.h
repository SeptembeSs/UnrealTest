// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LookComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NULLTEST_API ULookComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool LineTraceActor();
	
	bool CanSeeActor(FVector StartVector,FVector EndVector,TArray<const AActor*> Ignore) const;

	TObjectPtr<AActor> TargetActor;

	bool bCanSeeActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }
	FORCEINLINE void SetTargetActor(AActor* Actor) { TargetActor = Actor; }

	FORCEINLINE bool CanSeeActor() const { return bCanSeeActor; }
	FORCEINLINE void SetCanSeeActor(bool CanSee) { bCanSeeActor = CanSee; }
};
