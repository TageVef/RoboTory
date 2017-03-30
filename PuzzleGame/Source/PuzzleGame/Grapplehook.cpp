// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Grapplehook.h"
#include "MainPlayer.h"
#include "MovableObject.h"
#include "Door.h"


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
	SpawnRotation = GetActorRotation();

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

	if (this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Difference: %f"), DifferenceBetween.Size())
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
		/*ReturnVelocity = TempLocation - SpawnLocation;
		Cast<UPrimitiveComponent>(RootComponent)->AddImpulse(ReturnVelocity * -1.5, NAME_None, true);
		UE_LOG(LogTemp, Warning, TEXT("Går bakover på en veldig rar måte!"))*/
		bHitWall = false;

		CheckDestroy();
	}

	else
	{
		Cast<UPrimitiveComponent>(RootComponent)->AddImpulse(LaunchVelocity * -1, NAME_None, true);
		bMovingBack = true;
		UE_LOG(LogTemp, Warning, TEXT("Går bakover!"))
	}

	CheckDestroy();
	
}

void AGrapplehook::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{

	if (!OtherActor->IsA(AMovableObject::StaticClass()))
	{
		bHitWall = true;
		TempLocation = GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Kolliderte med veggen!"))
		LaunchBackwards(bMovingBack);
	}

	else
	{
		bHitWall = true;	
		CheckDestroy();

		HitBox = OtherActor;
		Cast<AMovableObject>(HitBox)->SetActorRotation(SpawnRotation);
		Cast<AMovableObject>(HitBox)->LaunchObject();
	
	}
}

void AGrapplehook::CheckDestroy()
{
	if (DifferenceBetween.Size() <= 100.f || bHitWall)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy hook!"))
			this->Destroy();
		bMovingBack = false;
		Cast<AMainPlayer>(PlayerThatShoot)->bShooting = false;
	}
	
}
