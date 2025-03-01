// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LookComponent.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookComponent::ULookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULookComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void ULookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bCanSeeActor = LineTraceActor();
}

bool ULookComponent::LineTraceActor()
{
	if (TargetActor == nullptr)
		return false;
	FVector StartLocation = GetComponentLocation();
	FVector EndLocation = TargetActor->GetActorLocation();
	TArray<const AActor*> IgnoreActors = {TargetActor,GetOwner()};
	// IgnoreActors.Add(TargetActor);
	// IgnoreActors.Add(GetOwner());
	if (CanSeeActor( StartLocation, EndLocation,IgnoreActors))
	{
		FRotator Direction = UKismetMathLibrary::FindLookAtRotation(StartLocation,EndLocation);
		FRotator* ResultDirection = new FRotator(0.0f,Direction.Yaw,Direction.Roll);
		GetOwner()->SetActorRotation(*ResultDirection);
		return true;
	}
	return false;
}

bool ULookComponent::CanSeeActor(FVector StartVector, FVector EndVector, TArray<const AActor*> Ignore) const
{
	if (TargetActor == nullptr)
		return false;
	FHitResult Hit;
	//自定义 Channel
	ECollisionChannel CollisionChannel = ECC_GameTraceChannel1;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(Ignore);

	//single trace
	GetWorld()->LineTraceSingleByChannel(Hit,StartVector,EndVector,CollisionChannel,Params);
	//Objects on the path
	// GetWorld()->LineTraceMultiByChannel(TArrayResult,StartVector,EndVector,CollisionChannel,Params);

	if (!Hit.bBlockingHit)
	{
		DrawDebugLine(GetWorld(),StartVector,EndVector,FColor::Red);
	}
	else
	{
		DrawDebugLine(GetWorld(),StartVector,EndVector,FColor::Green);
	}
	
	return !Hit.bBlockingHit;
}



