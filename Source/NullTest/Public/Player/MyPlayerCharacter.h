// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Interface/HealthInterface.h"
#include "MyPlayerCharacter.generated.h"

class AACPPPlayerController;
class UHealthComponent;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class NULLTEST_API AMyPlayerCharacter : public ACharacter,public IHealthInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UFUNCTION test
	UFUNCTION(BlueprintCallable)
	void CallableFunction();

	//UPROPERTY test
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float testLengths;

	//BlueprintIpmlEvent
	UFUNCTION(BlueprintImplementableEvent)
	void MyBlueprintFunction();

	UFUNCTION()
	void OnPlayerDestroyed(AActor* DestroyedActor);
	
	//move setting function
	void InitCharacterStatus();
	
	void InitInputController() const;
	
	void LookActionFunction(const FInputActionValue& InputActionValue);

	void MoveActionFunction(const FInputActionValue& InputActionValue);

	void JumpActionFunction(const FInputActionValue& InputActionValue);

	void StopMoveActionFunction(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Component")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Score")
	int Score;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Move")
	bool IsMove;

private:

	//Camera Setting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> PlayerCamera;
	
	//Input Setting
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> DefeatMapping;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> JumpAction;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnDeath_Implementation() override;

	virtual void OnDamage_Implementation() override;

	FORCEINLINE float GetScore() const { return Score; }
	void SetScore(int Value);

	UFUNCTION()
	void PlayerSaveGame();
	
	UFUNCTION()
	void PlayerLoadGame();
};

//枚举类
UENUM(BlueprintType)
enum class PLAYERSTATUS : uint8
{
	STAND,
	JUMP,
	RUN,
	DEAD
};
