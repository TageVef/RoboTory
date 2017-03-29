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

	//CollisionBox = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBox"));
	CollisionBox = FindComponentByClass<USphereComponent>();
	//CollisionBox->bGenerateOverlapEvents = true;
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGrapplehook::OnOverlap);

	LaunchVelocity = GetActorForwardVector() * 1000000;
	Cast<UPrimitiveComponent>(RootComponent)->AddForce(LaunchVelocity);
}

// Called every frame
void AGrapplehook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	

	
	//launch i en retning

	//launch tilbake

	//destory()

	/*NewLocation = GetActorLocation();

	Movement = GetActorForwardVector() * Speed * DeltaTime;

	if (!HitBox)
	{
		NewLocation += Movement;
		DespawnTime -= DeltaTime;
	}
	else if (HitBox)
	{
		if (HitBox->IsA(AMovableObject::StaticClass()))
		{
			if (Cast<AMovableObject>(HitBox)->bHit)
			{

				Cast<AMovableObject>(HitBox)->MoveObject(Movement);
				
			}
		}
		NewLocation -= Movement;
		DespawnTime += DeltaTime;
	}

	if (DespawnTime > 1.f)
	{
			if (PlayerThatShoot->IsA(AMainPlayer::StaticClass()))
			{
					Cast<AMainPlayer>(PlayerThatShoot)->bShooting = false;
				Cast<AMainPlayer>(PlayerThatShoot)->HookThatWasShoot = nullptr;
				Destroy();
			}
	}
	else if (DespawnTime < 0.5f)
	{
		NewLocation -= Movement;
		NewLocation -= Movement;
	}

	if (DespawnTime < 0.f)
	{
		if (PlayerThatShoot->IsA(AMainPlayer::StaticClass()))
		{
			Cast<AMainPlayer>(PlayerThatShoot)->bShooting = false;
			Cast<AMainPlayer>(PlayerThatShoot)->HookThatWasShoot = nullptr;
			Destroy();
		}
		
	}
	SetActorLocation(NewLocation, false);*/



}


void AGrapplehook::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult &Sweepresult)
{
	if (OtherActor->IsRootComponentStatic())
	{
		HitBox = OtherActor;
	}

	if (OtherActor->IsA(AMovableObject::StaticClass()))
	{
		HitBox = OtherActor;
		UE_LOG(LogTemp, Warning, TEXT("Den traff"))
		Cast<AMovableObject>(HitBox)->SetHit(true);
		FVector Offset = GetActorLocation() + (GetActorForwardVector() * 50.0f);
		OtherActor->SetActorLocation(Offset);
	}
}