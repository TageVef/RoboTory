// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Lever.h"
#include "Door.h"


// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));


}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WhatToActivate)
	{
		if (bHit)
		{
			Cast<ADoor>(WhatToActivate)->OpenDoor();
			UE_LOG(LogTemp, Warning, TEXT("Aaaaand open!"))
		}
		else
		{
			Cast<ADoor>(WhatToActivate)->CloseDoor();
		}
	}
}

void ALever::FlipHit()
{
	bHit = !bHit;

	UE_LOG(LogTemp, Warning, TEXT("bHit = %s"), bHit? TEXT("true") : TEXT("false"))
}
