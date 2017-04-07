// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MovableObject.generated.h"

UCLASS()
class PUZZLEGAME_API AMovableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* VisibleComponent = nullptr;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* SkeletonMesh = nullptr;*/

	/*UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox = nullptr;*/

	FVector StartLocation;
	FVector EndLocation;

	AActor* Grapplehook = nullptr;
	ACharacter* PlayerCharacter;

	bool bHit = false;

	bool GetHit();

	void SetHit(bool asdf);
	
	void SetEndLocation(FVector Location);

	void MoveObject(FVector DirectionSpeed);

	void LaunchObject(FVector StartLocation);
};
