// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "PressurePlate.h"
#include "Door.h"


// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Root Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	// Create Mesh Component
	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pressure Plate Mesh"));

	// Create TriggerVolume
	CollisionBox = CreateDefaultSubobject<ATriggerVolume>(TEXT("Collision Box"));



}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CollisionBox->IsOverlappingActor(ObjectThatActivates))
	{
		Cast<ADoor>(DoorThatOpens)->OpenDoor();
	}
	else
	{
		Cast<ADoor>(DoorThatOpens)->CloseDoor();
	}

}

