// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MainPlayer.h"
#include "Grapplehook.h"
#include "GrapplePoint.h"


// Sets default values
AMainPlayer::AMainPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraBoom);

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	// Shows mouse cursor so you see where you aim (rotate)
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->MaxWalkSpeed = NormalRunningSpeed;

	if (bShooting)
	{
		SetWalkingSpeed(StopMovementSpeed);
	}
	else
	{
		SetWalkingSpeed(MaxWalkingSpeed);
		RotateTowardsMouse(DeltaTime, XPosition, YPosition);
		bShooting = false;
	}
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Action bindings
	InputComponent->BindAction("Climb", IE_Pressed, this, &AMainPlayer::Climb);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMainPlayer::Shoot);

	//Setting up Axis bindings
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
	GetWorld()->GetFirstPlayerController()->GetCharacter()->Jump();
}

void AMainPlayer::RotateTowardsMouse(float DeltaTime, float XPos, float YPos)
{

	// Find mouse position and put the result in a 2D vector
	GetWorld()->GetFirstPlayerController()->GetMousePosition(XPos, YPos);
	FVector2D MouseLocation = FVector2D(XPos, YPos);

	// Find the viewport centre
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D  ViewportCenter = FVector2D(ViewportSize.X / 2, ViewportSize.Y / 2);

	// Find the vector between viewport centre and mouse cursor
	FVector2D MouseDirection = MouseLocation - ViewportCenter;
	FVector RotationAngle = FVector(MouseDirection.X, MouseDirection.Y, 0);

	// Set offset so the character rotates correctly
	FRotator RotationOffset = FRotator(0.f, 90.f, 0.f);
	FRotationMatrix RotationMatrix(RotationOffset);
	FVector MyVector = RotationMatrix.TransformVector(RotationAngle);

	// Find the new rotation
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), MyVector.Rotation(), DeltaTime, RotateSpeed);

	//Rotate towards mouse cursor
	GetWorld()->GetFirstPlayerController()->SetControlRotation(NewRotation);
}

void AMainPlayer::Shoot()
{
	if (!bShooting)
	{
		bShooting = true;
		StartCameraShake();
		// Play shootsound
		UGameplayStatics::PlaySound2D(GetWorld(), ShootSound, 1.f, 1.f, 0.f);

		UWorld* World = GetWorld();
		if (World)
		{
			SpawnPoint = GetActorLocation() + (GetActorForwardVector() * 100.0f);
			FVector Location = SpawnPoint;
			FRotator Rotation = GetActorRotation();
			HookThatWasShoot = World->SpawnActor<AGrapplehook>(GrapplehookBlueprint, Location, Rotation);

			Cast<AGrapplehook>(HookThatWasShoot)->PlayerThatShoot = this;
		}
	}
	
}

void AMainPlayer::SetWalkingSpeed(float InWalkingSpeed)
{
	NormalRunningSpeed = InWalkingSpeed;
}

void AMainPlayer::LaunchPlayer(FVector HitLocation)
{
	GetWorld()->GetFirstPlayerController()->GetCharacter()->LaunchCharacter(((HitLocation - SpawnPoint) * 1.3f + FVector(0.f, 0.f, 400.f)), false, false);
}

void AMainPlayer::StartCameraShake_Implementation() //Function here, but implementation in Blueprint
{

}