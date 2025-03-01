// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionDetection/CollisionDetectionBox.h"

#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/MyPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ACollisionDetectionBox::ACollisionDetectionBox()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACollisionDetectionBox::BeginPlay()
{
	Super::BeginPlay();

	InitStatus();
	//计时
	GetWorldTimerManager().SetTimer(BoxMoveTimerHandle, this, &ACollisionDetectionBox::ChangeDistance,MoveTime,true,MoveTime);
}

// Called every frame
void ACollisionDetectionBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveControl();
}

void ACollisionDetectionBox::InitStatus()
{
	// 绑定碰撞事件
	StaticMeshComponent = FindComponentByClass<UStaticMeshComponent>();
	// StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	if (StaticMeshComponent)
	{
		// UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent is not nullptr"));
		StaticMeshComponent->OnComponentHit.AddDynamic(this, &ACollisionDetectionBox::OnHit);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent is nullptr"));
	}
	
	
	IsMaterialsChanged = false;
}

void ACollisionDetectionBox::ChangeDistance()
{
	MoveDistance = !MoveDistance;
}

void ACollisionDetectionBox::MoveControl()
{
	// UE_LOG(LogTemp, Warning, TEXT("MoveControl"));
	FVector TrueMoveVector;
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	if (MoveDistance)
	{
		TrueMoveVector = MoveVector * MoveSpeed * DeltaTime;
	}
	else
	{
		TrueMoveVector = - MoveVector * MoveSpeed * DeltaTime;
	}
	AddActorWorldOffset(TrueMoveVector);
}

void ACollisionDetectionBox::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyPlayerCharacter* MyPlayerCharacter = Cast<AMyPlayerCharacter>(OtherActor);
	if (MyPlayerCharacter && StaticMeshComponent)
	{
		if (!IsMaterialsChanged)
		{
			if (CollisionAfterMaterial)
			{
				StaticMeshComponent->SetMaterial(0,CollisionAfterMaterial);
				StaticMeshComponent->MarkRenderStateDirty();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("CollisionAfterMaterial is nullptr"));
			}
			
			const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("DelayChangeFlag"), this);
			UKismetSystemLibrary::Delay(this,1.5f,LatentInfo);
		}
	}
}

void ACollisionDetectionBox::DelayChangeFlag()
{
	if (!IsMaterialsChanged)
		IsMaterialsChanged = true;
}


