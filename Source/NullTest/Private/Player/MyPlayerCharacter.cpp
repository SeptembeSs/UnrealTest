// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Component/HealthComponent.h"
#include "Engine/LocalPlayer.h"
#include "Game/ACPPPlayerController.h"
#include "Game/MyNewMapSaveGame.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitCharacterStatus();

}

void AMyPlayerCharacter::InitCharacterStatus()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	//CameraBoom 设置到 RootComponent
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->SetRelativeRotation(FRotator(-40.0f, 0.0f, 0.0f));
	CameraBoom->bUsePawnControlRotation = true;

	//PlayerCamera 设置到 CameraBoom
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;

	//player 不跟随输入旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//player 根据运动方向转向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,400.0f,0.0f);

	//监听销毁事件
	OnDestroyed.AddDynamic(this,&AMyPlayerCharacter::OnPlayerDestroyed);

	Score = 0;
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitInputController();
	
}

void AMyPlayerCharacter::InitInputController() const
{
	const ULocalPlayer* Player = nullptr;
	if (GEngine && GetWorld())
	{
		Player = GEngine->GetFirstGamePlayer(GetWorld());
		//get input system
		if (Player)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
			if (DefeatMapping)
			{
				Subsystem->AddMappingContext(DefeatMapping,0);
			}
		}
	}

	AACPPPlayerController* PlayerController = Cast<AACPPPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		// UE_LOG(LogTemp, Warning, TEXT("init"));
		PlayerController->UpdateHealthBar(HealthComponent->GetCurrentHealth(),HealthComponent->GetMaxHealth());
	}
}

void AMyPlayerCharacter::CallableFunction()
{
	//控制台log
	// UE_LOG(LogTemp, Warning, TEXT("CallableFunction"));

	//屏幕信息打印
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("CallableFunction"));
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (! IsMove)
	{
		//静止情况下，移动player防止跳过碰撞检测
		FVector* NewLocation = new FVector(0.01, 0, 0);
		FRotator* NewRotation = new FRotator(0, 0, 0);
		GetCharacterMovement()->MoveUpdatedComponent(*NewLocation,*NewRotation,false);
		NewLocation = new FVector(-0.01, 0, 0);
		GetCharacterMovement()->MoveUpdatedComponent(*NewLocation,*NewRotation,false);
	}
}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&AMyPlayerCharacter::LookActionFunction);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMyPlayerCharacter::MoveActionFunction);
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Canceled,this,&AMyPlayerCharacter::StopMoveActionFunction);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&AMyPlayerCharacter::JumpActionFunction);
	}
}

void AMyPlayerCharacter::OnDeath_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDeath_Implementation"));
	//QuitGame
	// UKismetSystemLibrary::QuitGame(this,nullptr,EQuitPreference::Quit,true);
	AACPPPlayerController* PlayerController = Cast<AACPPPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->ShowRestartWidget();
	}
}

void AMyPlayerCharacter::OnDamage_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDamage_Implementation"));
	AACPPPlayerController* PlayerController = Cast<AACPPPlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->UpdateHealthBar(HealthComponent->GetMaxHealth(),HealthComponent->GetCurrentHealth());
	}
}

void AMyPlayerCharacter::SetScore(int Value)
{
	Score = Value;
	AACPPPlayerController* PlayerController = Cast<AACPPPlayerController>(GetController());
	if (PlayerController != nullptr)
		PlayerController->UpdateScore(Value);
}

void AMyPlayerCharacter::LookActionFunction(const FInputActionValue& InputActionValue)
{
	FVector2d LookVector = InputActionValue.Get<FVector2d>();
	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void AMyPlayerCharacter::MoveActionFunction(const FInputActionValue& InputActionValue)
{
	FVector2D MoveVector = InputActionValue.Get<FVector2d>();
	if (Controller)
	{
		IsMove = true;
		const FRotator ControlRotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f,ControlRotation.Yaw,0.0f);
 
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
 
		AddMovementInput(ForwardDirection,MoveVector.Y);
		AddMovementInput(RightDirection, MoveVector.X);
	}
}

void AMyPlayerCharacter::JumpActionFunction(const FInputActionValue& InputActionValue)
{
	bool IsJump = InputActionValue.Get<bool>();
	if (Controller)
	{
		Jump();
	}
}

void AMyPlayerCharacter::StopMoveActionFunction(const FInputActionValue& InputActionValue)
{
	if (Controller)
	{
		IsMove = false;
	}
}

void AMyPlayerCharacter::OnPlayerDestroyed(AActor* DestroyedActor)
{
	UWorld* World = GetWorld();
	//restart current level
	UGameplayStatics::OpenLevel(World,FName(UGameplayStatics::GetCurrentLevelName(World)));
}

// void AMyPlayerCharacter::PlayerSaveGame()
// {
// 	// UMyNewMapSaveGame* SaveGameInstance = UGameplayStatics::CreateSaveGameObject(UMyNewMapSaveGame::StaticClass());
// 	// UGameplayStatics::SaveGameToSlot(SaveGameInstance, "FirstSaveSlot", 0);
//
// 	
// }
//
// void AMyPlayerCharacter::PlayerLoadGame()
// {
// }



