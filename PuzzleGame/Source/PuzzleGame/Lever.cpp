// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "Lever.h"
#include "Door.h"


// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeverMesh"));
	CollisionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WhatToActivate)
	{
		if (bHit)
		{
			Cast<ADoor>(WhatToActivate)->OpenDoor();
		}
		else
		{
			Cast<ADoor>(WhatToActivate)->CloseDoor();
		}
	}
	if (WhatToActivate2)
	{
		if (bHit)
		{
			Cast<ADoor>(WhatToActivate2)->OpenDoor();
		}
		else
		{
			Cast<ADoor>(WhatToActivate2)->CloseDoor();
		}
	}
	if (WhatToActivate3)
	{
		if (bHit)
		{
			Cast<ADoor>(WhatToActivate3)->OpenDoor();
		}
		else
		{
			Cast<ADoor>(WhatToActivate3)->CloseDoor();
		}
	}
	if (WhatToActivate4)
	{
		if (bHit)
		{
			Cast<ADoor>(WhatToActivate4)->OpenDoor();
		}
		else
		{
			Cast<ADoor>(WhatToActivate4)->CloseDoor();
		}
	}
}

void ALever::FlipHit()
{
	bHit = !bHit;
}
