// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MainPlayer.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Possesing controlls
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create Rootcomponent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	// Creating Mesh Object
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Mesh Component"));

	// Creating Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

	// Attaching Visual and camera to Root
	VisualMesh->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(-1000.0f, 0.0f, 1000.0f));
	CameraComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Movement.IsZero())
	{
		FVector Location = GetActorLocation() + (Movement * DeltaTime);
		SetActorLocation(Location);
	}

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Action bindings
	InputComponent->BindAction("Climb", IE_Pressed, this, &AMainPlayer::Climb);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayer::Interact);

	//Settign up Axis bindings
	InputComponent->BindAxis("MoveX", this, &AMainPlayer::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMainPlayer::MoveY);


}

void AMainPlayer::MoveX(float AxisValue)
{
	Movement.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}

void AMainPlayer::MoveY(float AxisValue)
{
	Movement.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}

void AMainPlayer::Climb()
{
}

void AMainPlayer::Interact()
{
}

