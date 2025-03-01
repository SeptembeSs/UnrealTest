// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnim.generated.h"

class UCharacterMovementComponent;
class AMyPlayerCharacter;
/**
 * 
 */
UCLASS()
class NULLTEST_API UMyPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyPlayerCharacter> MyPlayerCharacter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> MyPlayerCharacterMovement;

	UPROPERTY(BlueprintReadOnly)
	float MyPlayerMovementSpeed;

	UPROPERTY(blueprintReadOnly)
	bool IsPressedJump;

	UPROPERTY(blueprintReadOnly)
	bool IsReleasedJump;

	UPROPERTY(blueprintReadOnly)
	bool IsFalling;
	
};
