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
	this->OnActorHit.AddDynamic(this, &AGrapplehook::OnHit);

	LaunchVelocity = GetActorForwardVector() * Speed; //Launches the Hook in forward direction on spawn
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


void AGrapplehook::LaunchForward() //Launches the hook forward
{
	Cast<UPrimitiveComponent>(RootComponent)->AddImpulse(LaunchVelocity, NAME_None, true);
}

void AGrapplehook::LaunchBackwards(bool &bMovingBack) //Launches the hook backwards
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
	// Play hitsound
	UGameplayStatics::PlaySound2D(GetWorld(), HitSound, 1.f, 1.f, 0.f);

	if (OtherActor->IsA(AGrapplePoint::StaticClass())) //if hit by GrapplePoint
	{
		bHitWall = true;
		CheckDestroy();
		HitBox = OtherActor;
		Location = Cast<AGrapplePoint>(HitBox)->GetActorLocation();
		Cast<AMainPlayer>(PlayerThatShoot)->LaunchPlayer(Location); //Launch Player towards GrapplePoint
	}
	else if (OtherActor->IsA(ALever::StaticClass())) //if Lever
	{
		bHitWall = true;
		CheckDestroy();
		HitBox = OtherActor;
		Cast<ALever>(HitBox)->FlipHit(); //Flip the switch
	}
	else if (OtherActor->IsA(AMovableObject::StaticClass())) //if MoveableObject
	{
		bHitWall = true;	
		CheckDestroy();
		HitBox = OtherActor;
		FVector WhereIsPlayer = Cast<AMainPlayer>(PlayerThatShoot)->GetActorLocation();
		Cast<AMovableObject>(HitBox)->LaunchObject(WhereIsPlayer);	//Launch the object towards the player
	}
	else //if anything else (mostly walls)
	{
		bHitWall = true;
		CheckDestroy(); //destroy
		LaunchBackwards(bMovingBack);
	}
}

void AGrapplehook::CheckDestroy() //checks if it should destroy itself or not
{
	if (DifferenceBetween.Size() <= 60.f || bHitWall)
	{
		this->Destroy();
		bMovingBack = false;
		Cast<AMainPlayer>(PlayerThatShoot)->bShooting = false;
	}
	
}
