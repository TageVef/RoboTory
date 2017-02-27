// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class PUZZLEGAME_API ADoor : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorMesh;
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector StarterLocation;
	FVector Movement = FVector(0, 0, 0);

	void OpenDoor();

	void CloseDoor();
	
	
};
