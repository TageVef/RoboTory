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

	/// Movement X Values and Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		bool MoveDirectionX = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		float MovementSpeedForward = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		float MoveXValue = 250.f;
	
	/// Movement Y Values and Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		bool MoveDirectionY = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		float MovementSpeedRight = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		float MoveYValue = 250.f;

	/// Movement Z Values and Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		bool MoveDirectionZ = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		float MovementSpeedUp = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction and movement")
		float MoveZValue = 250.f;
	

	void OpenDoor();

	void CloseDoor();
	
	
};
