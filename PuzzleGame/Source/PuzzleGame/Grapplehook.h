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

	UPROPERTY(EditAnywhere)
	UShapeComponent* CollisionBox;
	// The speed of the grapplehook
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int Speed = 1800;
	// How far will the grapplehook go before it returns to spawnpoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int DistanceBeforeReturn = 500;

	AActor* PlayerThatShoot = nullptr;
	AActor* ActorHit = nullptr;

	void LaunchForward();
	void CheckDestroy();

	UPROPERTY(BlueprintReadWrite)
		FVector WhereIsPlayer;
	UPROPERTY(EditAnywhere)
		USoundBase* HitSound;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, 
			FVector NormalImpulse, const FHitResult& Hit);

private:
	AActor* HitBox = nullptr;
	FVector Movement;
	FVector LaunchVelocity;
	FVector SpawnLocation;
	FVector DifferenceBetween;
	FVector Location;

	bool bMovingBack = false;
	bool bHitWall = false;
};
