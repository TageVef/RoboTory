// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MainPlayer.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));

	CameraBoom->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraBoom);

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
	AddMovementInput(FVector::ForwardVector, AxisValue);
}

void AMainPlayer::MoveY(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);
}

void AMainPlayer::Climb()
{
}

void AMainPlayer::Interact()
{
}

void AMainPlayer::RotateTowardsMouse(float DeltaTime)
{
}

