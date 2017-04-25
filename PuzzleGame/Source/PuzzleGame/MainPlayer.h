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

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UPROPERTY(EditAnywhere, Category = "Grapplehook")
		TSubclassOf<class AGrapplehook> GrapplehookBlueprint;

	/// Is this in use?
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AMovableObject> DragBox;

	UPROPERTY(EditAnywhere)
		float RotateSpeed = 350.f;

	AActor* MovableObject = nullptr;
	
	float XPosition;
	float YPosition;

	UPROPERTY(EditAnywhere)
		float NormalRunningSpeed = 300.f;
	float const StopMovementSpeed = 0.f;
	float WalkingSpeed = NormalRunningSpeed;

	FVector WalkingVector = GetActorForwardVector() * (WalkingSpeed);
	bool Holding = false;
	float ShootTimer = 1.f;


	void MoveX(float AxisValue);

	void MoveY(float AxisValue);

	void Climb();

	void Interact();

	void StopInteract();

	void RotateTowardsMouse(float DeltaTime, float XPos, float YPos);

	void Shoot();

	void AlternateShoot();

	void SetWalkingSpeed(float InWalkingSpeed);

public:

	AActor* HookThatWasShoot = nullptr;
	UPROPERTY(BlueprintReadWrite)
	bool bShooting = false;
	FVector StartLineTrace;
	FVector EndLineTrace;
	FHitResult Hit;
	FVector WhereIsHook;

	bool bCanReadSign = false;
	bool bReadingSign = false;

	void LaunchPlayer(FVector HitLocation);
	void LaunchPlayerTest();
};
