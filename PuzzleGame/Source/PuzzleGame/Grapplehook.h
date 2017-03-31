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

	AActor* HitBox = nullptr;
	FVector Movement;
	FVector NewLocation;

	ACharacter* PlayerCharacter;
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
	AActor* ActorHit = nullptr;
	FVector LaunchVelocity;
	FVector ReturnVelocity;

	// Alot of locations. Dont know if theyre all in use
	FVector SpawnLocation;
	FVector ReturnLocation;
	FRotator SpawnRotation;
	FVector DifferenceBetween;
	FVector Location;
	FVector TempLocation;
	FVector CollisionLocation;

	bool bMovingBack = false;
	bool bHitWall = false;

	// The speed of the grapplehook
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int Speed = 1300;

	// How far will the grapplehook go before it returns to spawnpoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int DistanceBeforeReturn = 700;

	void LaunchForward();
	void LaunchBackwards(bool &bMovingBack);
	void CheckDestroy();


	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, 
			FVector NormalImpulse, const FHitResult& Hit);

};
