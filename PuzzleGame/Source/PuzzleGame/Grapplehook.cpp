// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Grapplehook.h"
#include "MainPlayer.h"
#include "MovableObject.h"


// Sets default values
AGrapplehook::AGrapplehook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBox"));
	CollisionBox->bGenerateOverlapEvents = true;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGrapplehook::OnOverlap);


}

// Called when the game starts or when spawned
void AGrapplehook::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
}

// Called every frame
void AGrapplehook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	// There is a problem somewhere, character is shooting from the right side, not the front.
	// Probably something wrong in the RotateTowardsMouse() function.
	NewLocation += GetActorRightVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation, false);
	DespawnTime -= DeltaTime;

	if (DespawnTime < 0)
	{
		this->Destroy();
	}

}


void AGrapplehook::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult &Sweepresult)
{
	
	if (OtherActor->IsA(AMovableObject::StaticClass()))
	{
		AMovableObject* HitBox = Cast<AMovableObject>(OtherActor);
		
		UE_LOG(LogTemp, Warning, TEXT("Den traff"))
		HitBox->SetHit(true);
		HitBox->SetEndLocation(StartLocation);

		this->Destroy();
	}
}