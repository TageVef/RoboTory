// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lever.generated.h"

UCLASS()
class PUZZLEGAME_API ALever : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bHit = false;

	void FlipHit();

private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LeverMesh;
	UPROPERTY(EditAnywhere)
		AActor* WhatToActivate;



	
	
};
