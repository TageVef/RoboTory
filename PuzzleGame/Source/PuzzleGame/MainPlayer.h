// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class PUZZLEGAME_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UPROPERTY(EditAnywhere, Category = "Grapplehook")
		TSubclassOf<class AGrapplehook> GrapplehookBlueprint;

	UPROPERTY(EditAnywhere)
		float RotateSpeed = 350.f;
	
	float XPosition;
	float YPosition;

	UPROPERTY(EditAnywhere)
	float NormalRunningSpeed = 300.f;
	float const MaxWalkingSpeed = 300.f;
	float const StopMovementSpeed = 0.f;

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void Climb();
	void RotateTowardsMouse(float DeltaTime, float XPos, float YPos);
	void Shoot();
	void SetWalkingSpeed(float InWalkingSpeed);

public:

	AActor* HookThatWasShoot = nullptr;
	FVector SpawnPoint;
	FHitResult Hit;

	FVector WhereIsHook;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bShooting = false;

	void LaunchPlayer(FVector HitLocation);

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
		UCameraComponent* PlayerCamera = nullptr;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void StartCameraShake();
	UPROPERTY(EditAnywhere)
		USoundBase* ShootSound;
	
};
