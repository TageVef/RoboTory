// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Door.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	StarterLocation = GetActorLocation();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime) //Moves the door every frame.
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation() + (Movement * DeltaTime);

	if (MoveDirectionX)
	{
		Location.X = FMath::Clamp(Location.X, StarterLocation.X, StarterLocation.X + MoveXValue);
	}

	if (MoveDirectionY)
	{
		Location.Y = FMath::Clamp(Location.Y, StarterLocation.Y, StarterLocation.Y + MoveYValue);
	}

	if (MoveDirectionZ)
	{
		Location.Z = FMath::Clamp(Location.Z, StarterLocation.Z, StarterLocation.Z + MoveZValue);
	}

	SetActorLocation(Location);

}


void ADoor::OpenDoor() //setting movement in the direction it is suppose to go.
{
	if (MoveDirectionX)
	{
		Movement = GetActorForwardVector() * MovementSpeedForward;
	}

	if (MoveDirectionY)
	{
		Movement = GetActorRightVector() * MovementSpeedRight;
	}

	if (MoveDirectionZ)
	{
		Movement = GetActorUpVector() * MovementSpeedUp;
	}
	
}

void ADoor::CloseDoor() //setting direction for the oppisit direction
{
	if (MoveDirectionX)
	{
		Movement = GetActorForwardVector() * -MovementSpeedForward;
	}

	if (MoveDirectionY)
	{
		Movement = GetActorRightVector() * -MovementSpeedRight;
	}

	if (MoveDirectionZ)
	{
		Movement = GetActorUpVector() * -MovementSpeedUp;
	}
	
}

