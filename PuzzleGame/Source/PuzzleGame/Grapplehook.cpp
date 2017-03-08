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
	
}

// Called every frame
void AGrapplehook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	NewLocation = GetActorLocation();

	Movement = GetActorForwardVector() * Speed * DeltaTime;

	if (!HitBox)
	{
		NewLocation += Movement;
		DespawnTime -= DeltaTime;
	}
	else if (HitBox)
	{
		if (Cast<AMovableObject>(HitBox)->bHit)
		{
			NewLocation -= Movement;
			Cast<AMovableObject>(HitBox)->MoveObject(Movement);
			DespawnTime += DeltaTime;
		}
	}

	if (DespawnTime > 1.f)
	{
		Cast<AMovableObject>(HitBox)->bHit = false;
		Destroy();
	}

	SetActorLocation(NewLocation, false);

	if (DespawnTime < 0.5f)
	{
		NewLocation -= Movement;
		NewLocation -= Movement;
		SetActorLocation(NewLocation, false);
	}

	if (DespawnTime < 0.f)
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
		HitBox = OtherActor;
		UE_LOG(LogTemp, Warning, TEXT("Den traff"))
		Cast<AMovableObject>(HitBox)->SetHit(true);
		FVector Offset = GetActorLocation() + (GetActorForwardVector() * 50.0f);
		OtherActor->SetActorLocation(Offset);
	}
}