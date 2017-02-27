// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation() + (Movement * DeltaTime);

	Location.Z = FMath::Clamp(Location.Z, StarterLocation.Z, StarterLocation.Z + 200.0f);

	SetActorLocation(Location);

}

void ADoor::OpenDoor()
{
	Movement = GetActorUpVector() * 200.0f;
}

void ADoor::CloseDoor()
{
	Movement = GetActorUpVector() * -200.0f;
}

