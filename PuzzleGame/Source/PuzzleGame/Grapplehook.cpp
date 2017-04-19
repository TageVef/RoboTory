// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Grapplehook.h"
#include "MainPlayer.h"
#include "MovableObject.h"
#include "Door.h"
#include "GrapplePoint.h"
#include "Lever.h"


// Sets default values
AGrapplehook::AGrapplehook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AGrapplehook::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox = FindComponentByClass<USphereComponent>();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGrapplehook::OnOverlap);
	this->OnActorHit.AddDynamic(this, &AGrapplehook::OnHit);

	LaunchVelocity = GetActorForwardVector() * Speed;
	LaunchForward();
	
	SpawnLocation = GetActorLocation();
}

// Called every frame
void AGrapplehook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Location = GetActorLocation();

	// Find the difference between the vectors
	DifferenceBetween = Location - SpawnLocation;

	// If the lenght between them is greater than X, launch the hook back
	if (DifferenceBetween.Size() >= DistanceBeforeReturn)
	{
		LaunchBackwards(bMovingBack);
	}
	
	// If the hook is moving back to the player, check if the destroy criteria have been met
	if (bMovingBack)
	{
		CheckDestroy();
	}

	
	
}


void AGrapplehook::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult &Sweepresult)
{
	//if (OtherActor->IsRootComponentStatic())
	//{
	//	HitBox = OtherActor;
	//}

	//if (OtherActor->IsA(AMovableObject::StaticClass()))
	//{
	//	HitBox = OtherActor;
	//	UE_LOG(LogTemp, Warning, TEXT("Den traff"))
	//	Cast<AMovableObject>(HitBox)->SetHit(true);
	//	FVector Offset = GetActorLocation() + (GetActorForwardVector() * 50.0f);
	//	OtherActor->SetActorLocation(Offset);
	//}
}

void AGrapplehook::LaunchForward()
{
	Cast<UPrimitiveComponent>(RootComponent)->AddImpulse(LaunchVelocity, NAME_None, true);
}

void AGrapplehook::LaunchBackwards(bool &bMovingBack)
{
	if (bHitWall)
	{
		bHitWall = false;

		CheckDestroy();
	}

	else
	{
		Cast<UPrimitiveComponent>(RootComponent)->AddImpulse(LaunchVelocity * -1, NAME_None, true);
		bMovingBack = true;
	}

	CheckDestroy();
	
}

void AGrapplehook::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(AGrapplePoint::StaticClass()))
	{
		bHitWall = true;
		CheckDestroy();

		HitBox = OtherActor;
		FVector Location = Cast<AGrapplePoint>(HitBox)->GetActorLocation();

		if (this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Difference: %f"), DifferenceBetween.Size())
		}

		Cast<AMainPlayer>(PlayerThatShoot)->LaunchPlayer(Location);
	}

	else if (OtherActor->IsA(ALever::StaticClass()))
	{
		bHitWall = true;
		CheckDestroy();

		HitBox = OtherActor;

		Cast<ALever>(HitBox)->FlipHit();
	}

	else if (!OtherActor->IsA(AMovableObject::StaticClass()))
	{
		bHitWall = true;
		CheckDestroy();
		TempLocation = GetActorLocation();

		if (this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Difference: %f"), DifferenceBetween.Size())
		}

		LaunchBackwards(bMovingBack);
	}

	else
	{
		bHitWall = true;	
		CheckDestroy();

		if (this)
		{
			UE_LOG(LogTemp, Warning, TEXT("Difference: %f"), DifferenceBetween.Size())
		}

		HitBox = OtherActor;

		FVector WhereFrom = Cast<AMainPlayer>(PlayerThatShoot)->StartLineTrace;

		Cast<AMovableObject>(HitBox)->LaunchObject(WhereFrom);
	}
}

void AGrapplehook::CheckDestroy()
{
	if (DifferenceBetween.Size() <= 10.f || bHitWall)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy hook!"))
		this->Destroy();
		bMovingBack = false;
		Cast<AMainPlayer>(PlayerThatShoot)->bShooting = false;
	}
	
}
