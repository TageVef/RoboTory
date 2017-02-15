// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS()
class PUZZLEGAME_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

	float Speed{ 800.0f };

	FVector Movement;

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

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraComponent;

	void MoveX(float AxisValue);

	void MoveY(float AxisValue);

	void Climb();

	void Interact();

	
	
};
