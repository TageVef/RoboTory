// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class PUZZLEGAME_API APressurePlate : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PressurePlateMesh;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* CollisionBox;

	UPROPERTY(EditAnywhere)
	AActor* MainExitDoor;

	UPROPERTY(EditAnywhere)
	AActor* DoorThatOpens;

	UPROPERTY(EditAnywhere)
	AActor* DoorThatOpens2;

	UPROPERTY(EditAnywhere)
	AActor* ObjectThatActivates;

	UPROPERTY(EditAnywhere)
	AActor* ObjectThatActivates2;

	UPROPERTY(EditAnywhere)
	AActor* ObjectThatActivates3;

	UPROPERTY(EditAnywhere)
	bool PlayerCanActivate = false;

	/*UPROPERTY(EditAnywhere)
	bool AnyMovableObjectCanActivate = false;*/

	AActor* PlayerCharacter;
	//	AActor* MoveObject;
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
