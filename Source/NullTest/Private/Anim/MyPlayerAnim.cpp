// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/MyPlayerAnim.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/MyPlayerCharacter.h"

#include "Kismet/KismetMathLibrary.h"

void UMyPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	MyPlayerCharacter = Cast<AMyPlayerCharacter>(TryGetPawnOwner());
	if (MyPlayerCharacter)
	{
		MyPlayerCharacterMovement = MyPlayerCharacter -> GetCharacterMovement();
	}
}

void UMyPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (MyPlayerCharacterMovement)
	{
		MyPlayerMovementSpeed = UKismetMathLibrary::VSizeXY(MyPlayerCharacterMovement -> Velocity);
		// UE_LOG(LogTemp, Warning, TEXT("NativeUpdateAnimation"));
		
		if (MyPlayerCharacterMovement->IsFalling() && (MyPlayerCharacterMovement->Velocity.Z > 0))
		{
			IsPressedJump = true;
		}
		else
		{
			IsPressedJump = false;
		}
		// if (IsPressedJump)
		// 	UE_LOG(LogTemp, Warning, TEXT("IsPressedJump"));

		if (MyPlayerCharacterMovement->IsFalling() && (MyPlayerCharacterMovement->Velocity.Z < 0))
		{
			IsReleasedJump = true;
		}
		else
		{
			IsReleasedJump = false;
		}
		// if (IsReleasedJump)
		// 	UE_LOG(LogTemp, Warning, TEXT("IsReleasedJump"));

		IsFalling =  MyPlayerCharacterMovement -> IsFalling();
		// if (IsFalling)
		// 	UE_LOG(LogTemp, Warning, TEXT("IsFalling"));
		
	}
}
