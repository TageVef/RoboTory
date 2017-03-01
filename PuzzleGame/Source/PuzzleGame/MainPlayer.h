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

	//UPROPERTY(VisibleAnywhere)
	//	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UPROPERTY(EditAnywhere, Category = "Grapplehook")
		TSubclassOf<class AGrapplehook> GrapplehookBlueprint;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AMovableObject> DragBox;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult &Sweepresult);

	void MoveX(float AxisValue);

	void MoveY(float AxisValue);

	void Climb();

	void Interact();

	void RotateTowardsMouse(float DeltaTime, float XPos, float YPos);

	AActor* MovableObject = nullptr;

	float XPosition;
	float YPosition;
	float WalkingSpeed = 700.f;

	FVector WalkingVector = GetActorForwardVector() * (WalkingSpeed);
	bool Holding{ false };
	
	UPROPERTY(EditAnywhere)
		float RotateSpeed = 350.f;

	void Shoot();
	bool bShooting = false;
	float ShootTimer = .5f;
	float StartTimer;
	void SetWalkingSpeed(float InWalkingSpeed);

	
	
};
