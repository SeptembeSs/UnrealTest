// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BallProjecttile.h"

#include "Component/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerCharacter.h"

// Sets default values
ABallProjecttile::ABallProjecttile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereComponent->SetSphereRadius(35.f);
	//设置碰撞预设
	SphereComponent->SetCollisionProfileName("BallPreset");
	//设置hit属性
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->OnComponentHit.AddDynamic(this,&ABallProjecttile::OnBallProjectileHit);
	SetRootComponent(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	//move speed
	ProjectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void ABallProjecttile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(4.f);
	if (CreateSoundBase)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CreateSoundBase, GetActorLocation());
	}
}

// Called every frame
void ABallProjecttile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallProjecttile::OnBallProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitSoundBase != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this,HitSoundBase,GetActorLocation(),1,FMath::RandRange(0.4f,1.3f),0.0f
			,HitSoundAttenuation);
	}
	
	AMyPlayerCharacter* PlayerCharacter = Cast<AMyPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("hit player"));
		UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();
		if (HealthComponent)
		{
			HealthComponent->LoseHealth(Damage);
		}
		if (HitParticles != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation());
		}
		
		Destroy();
	}
	
}



