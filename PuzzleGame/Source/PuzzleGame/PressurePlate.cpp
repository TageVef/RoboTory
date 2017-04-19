// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "PressurePlate.h"
#include "Door.h"
#include "MovableObject.h"


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

	PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	// MoveObject = Cast<AMovableObject>(MoveObject);
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DoorThatOpens)
	{
		if (CollisionBox->IsOverlappingActor(ObjectThatActivates) ||
			CollisionBox->IsOverlappingActor(ObjectThatActivates2) ||
			CollisionBox->IsOverlappingActor(ObjectThatActivates3) ||
			(PlayerCanActivate && CollisionBox->IsOverlappingActor(PlayerCharacter)))
		{
			Cast<ADoor>(DoorThatOpens)->OpenDoor();
		}

		else
		{
			Cast<ADoor>(DoorThatOpens)->CloseDoor();
		}
	}

	if (DoorThatOpens2)
	{
		if (CollisionBox->IsOverlappingActor(ObjectThatActivates) ||
			CollisionBox->IsOverlappingActor(ObjectThatActivates2) ||
			CollisionBox->IsOverlappingActor(ObjectThatActivates3) ||
			(PlayerCanActivate && CollisionBox->IsOverlappingActor(PlayerCharacter)))
		{
			Cast<ADoor>(DoorThatOpens2)->OpenDoor();
		}

		else
		{
			Cast<ADoor>(DoorThatOpens2)->CloseDoor();
		}
	}
}

