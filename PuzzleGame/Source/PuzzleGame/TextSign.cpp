// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "TextSign.h"
#include "MainPlayer.h"


// Sets default values
ATextSign::ATextSign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	VisibleComponent->SetupAttachment(RootComponent);
	TriggerComponent = CreateDefaultSubobject<ATriggerVolume>(TEXT("TriggerVolume"));


}

// Called when the game starts or when spawned
void ATextSign::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
}

// Called every frame
void ATextSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TriggerComponent)
	{

		if (TriggerComponent->IsOverlappingActor(PlayerCharacter))
		{
			Cast<AMainPlayer>(PlayerCharacter)->bCanReadSign = true;

			if (Cast<AMainPlayer>(PlayerCharacter)->bReadingSign)
			{

			}
		}

		else if (!TriggerComponent->IsOverlappingActor(PlayerCharacter))
		{
			Cast<AMainPlayer>(PlayerCharacter)->bCanReadSign = false;
		}

	}

}

