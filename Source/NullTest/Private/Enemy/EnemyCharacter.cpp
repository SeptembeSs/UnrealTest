// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyCharacter.h"

#include <ranges>

#include "TimerManager.h"
#include "Component/HealthComponent.h"
#include "Component/LookComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile/BallProjecttile.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
	FTransform Transform = SkeletalMeshComponent->GetSocketTransform("head");

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(SkeletalMeshComponent);
	SceneComponent->SetRelativeLocation(Transform.GetTranslation());
	// UE_LOG(LogTemp, Warning, TEXT("Transform %s"),*Transform.ToString());
	
	LookComponent = CreateDefaultSubobject<ULookComponent>(TEXT("LookComponent"));
	LookComponent->SetupAttachment(SceneComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//get target player
	TargetCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	LookComponent->SetTargetActor(TargetCharacter);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// bCanSeeTargetCharacter = LineTraceActor(TargetCharacter);
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
			GetWorldTimerManager().SetTimer(BallProjectileTimerHandle,this,&AEnemyCharacter::CreateBallProjectile,BallInterval,true,BallDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(BallProjectileTimerHandle);
		}
	}
	bPerviousCanSeeTargetCharacter = bCanSeeTargetCharacter;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::CreateBallProjectile()
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

void AEnemyCharacter::OnDeath_Implementation()
{
	Destroy();
}

void AEnemyCharacter::OnDamage_Implementation()
{
	
}

//转为Component形式实现
// bool AEnemyCharacter::LineTraceActor(const AActor* TargetActor)
// {
// 	if (TargetActor == nullptr)
// 		return false;
// 	FVector StartLocation = GetActorLocation();
// 	FVector EndLocation = TargetActor->GetActorLocation();
// 	if (CanSeeActor(TargetActor, StartLocation, EndLocation))
// 	{
// 		FRotator Direction = UKismetMathLibrary::FindLookAtRotation(StartLocation,EndLocation);
// 		SetActorRotation(Direction);
// 		return true;
// 	}
// 	return false;
// }
//
// bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor, FVector StartVector, FVector EndVector)
// {
// 	if (TargetActor == nullptr)
// 		return false;
// 	FHitResult Hit;
// 	//自定义 Channel
// 	ECollisionChannel CollisionChannel = ECC_GameTraceChannel1;
// 	
//
// 	FCollisionQueryParams Params;
// 	Params.AddIgnoredActor(this);
// 	Params.AddIgnoredActor(TargetActor);
//
// 	//single trace
// 	GetWorld()->LineTraceSingleByChannel(Hit,StartVector,EndVector,CollisionChannel,Params);
// 	//Objects on the path
// 	GetWorld()->LineTraceMultiByChannel(TArrayResult,StartVector,EndVector,CollisionChannel,Params);
//
// 	if (!Hit.bBlockingHit)
// 	{
// 		DrawDebugLine(GetWorld(),StartVector,EndVector,FColor::Red);
// 	}
// 	else
// 	{
// 		DrawDebugLine(GetWorld(),StartVector,EndVector,FColor::Green);
// 	}
// 	
// 	return !Hit.bBlockingHit;
// }




