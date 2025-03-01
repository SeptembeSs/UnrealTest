// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionDetection/ScoreBox.h"

#include "Components/BoxComponent.h"
#include "Player/MyPlayerCharacter.h"

// Sets default values
AScoreBox::AScoreBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreBox::BeginPlay()
{
	Super::BeginPlay();

	InitComponents();
}

void AScoreBox::InitComponents()
{
	StaticMeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (!StaticMeshComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lost the StaticMeshComponent"));
	}

	BoxMesh = FindComponentByClass<UBoxComponent>();
	if (!BoxMesh)
	{
		BoxMesh = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	}
	if (BoxMesh)
	{
		// 启用重叠事件
		BoxMesh->SetGenerateOverlapEvents(true);
		// 设置碰撞响应（例如与所有物体发生重叠时触发）
		BoxMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
		BoxMesh->OnComponentBeginOverlap.AddDynamic(this,&AScoreBox::BoxBeginOverlap);
	}
}



// Called every frame
void AScoreBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveControl(DeltaTime);
}

void AScoreBox::MoveControl(float DeltaTime)
{
	FRotator RotationDelta = FRotator(0.f, 30.f * DeltaTime, 0.f);  // 每秒旋转 30 度
	AddActorLocalRotation(RotationDelta);
}

void AScoreBox::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyPlayerCharacter* PlayerCharacter = Cast<AMyPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("hit the score box"));
		PlayerCharacter->SetScore(PlayerCharacter->GetScore() + 1);
		Destroy();
	}
}
