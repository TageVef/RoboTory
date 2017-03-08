// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MovableObject.h"
#include "Grapplehook.h"


// Sets default values
AMovableObject::AMovableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneCaptureComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	VisibleComponent->SetupAttachment(RootComponent);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void AMovableObject::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMovableObject::GetHit()
{
	return bHit;
}

void AMovableObject::SetHit(bool asdf)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit er satt"))
	bHit = asdf;
}

void AMovableObject::SetEndLocation(FVector Location)
{
	EndLocation = Location;
}

void AMovableObject::MoveObject(FVector DirectionSpeed)
{
	if (bHit)
	{
		FVector Location = GetActorLocation() - (DirectionSpeed);

		// Keeps the same height on the movable objects affected by grapplehook
		Location.Z = StartLocation.Z;
		SetActorLocation(Location);
	}
}
