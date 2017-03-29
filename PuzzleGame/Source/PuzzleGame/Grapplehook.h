// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Grapplehook.generated.h"

UCLASS()
class PUZZLEGAME_API AGrapplehook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrapplehook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	

	UPROPERTY(EditAnywhere)
		float Speed = 1500.f;
	UPROPERTY(EditAnywhere)
		float DespawnTime = 1.f;

	AActor* HitBox = nullptr;
	FVector Movement;
	FVector NewLocation;

	ACharacter* PlayerCharacter = nullptr;
	FVector PCMovement;
	FVector PCNewLocation;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult &Sweepresult);

public:
	UPROPERTY(EditAnywhere)
	UShapeComponent* CollisionBox;

	AActor* PlayerThatShoot = nullptr;
	FVector LaunchVelocity;

};
