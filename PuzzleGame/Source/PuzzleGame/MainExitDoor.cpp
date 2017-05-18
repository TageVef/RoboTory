// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MainExitDoor.h"


// Sets default values
AMainExitDoor::AMainExitDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMainExitDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainExitDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainExitDoor::OpenDoor()
{
	RunAnimationOpen = true;
}

void AMainExitDoor::CloseDoor()
{
	RunAnimationOpen = false;
}
