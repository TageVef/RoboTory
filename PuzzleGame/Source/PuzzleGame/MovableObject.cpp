// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MovableObject.h"
#include "Grapplehook.h"
#include "MainPlayer.h"


// Sets default values
AMovableObject::AMovableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	VisibleComponent->SetupAttachment(CollisionBox);

	// SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMeshComponent"));
	// SkeletonMesh->SetupAttachment(RootComponent);

	/*CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->bGenerateOverlapEvents = true;
	CollisionBox->SetupAttachment(RootComponent);*/

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

	FVector Location = GetActorLocation();
	if (Location.Z < -300)
	{
		SetActorLocation(StartLocation);
	}
}


void AMovableObject::LaunchObject(FVector LaunchLocation)
{
	// Find the distance between the player and the box, add height based on distance.
	FVector DistanceBetween = LaunchLocation - GetActorLocation();
	float UpDistance = DistanceBetween.Size() * 0.47;
	FVector HowHigh = FVector(0.f, 0.f, UpDistance);

	// Use the vectors above to launch the object towards the player.
	Cast<UPrimitiveComponent>(RootComponent)->AddImpulse((LaunchLocation - GetActorLocation()) + HowHigh, NAME_None, true);
}
