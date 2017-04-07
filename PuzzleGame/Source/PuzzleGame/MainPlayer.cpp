// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleGame.h"
#include "MainPlayer.h"
#include "Grapplehook.h"
#include "MovableObject.h"


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

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	StartLineTrace = (GetActorLocation() + GetActorForwardVector() * 85) - FVector(0.f, 0.f, 50.f);
	EndLineTrace = (GetActorLocation() + GetActorForwardVector() * 785) - FVector(0.f, 0.f, 50.f);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	DrawDebugLine(GetWorld(), StartLineTrace, EndLineTrace, FColor::Red, false, 0.f, 0, 5.f);

	if (bShooting)
	{
		SetWalkingSpeed(StopMovementSpeed);
	}
	else
	{
		SetWalkingSpeed(NormalRunningSpeed);
		RotateTowardsMouse(DeltaTime, XPosition, YPosition);

		GetWorld()->LineTraceSingleByObjectType(Hit, StartLineTrace, EndLineTrace,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

		bShooting = false;
	}


	/*if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Trace hit: %s"), *Hit.GetActor()->GetName())
	}*/


}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Action bindings
	InputComponent->BindAction("Climb", IE_Pressed, this, &AMainPlayer::Climb);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayer::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &AMainPlayer::StopInteract);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMainPlayer::Shoot);
	InputComponent->BindAction("AlternateShoot", IE_Pressed, this, &AMainPlayer::AlternateShoot);

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

void AMainPlayer::Interact()
{
	Holding = true;
	SetWalkingSpeed(200.f);

	LaunchPlayerTest();
}

void AMainPlayer::StopInteract()
{
	Holding = false;
	SetWalkingSpeed(400.f);
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

		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = StartLineTrace;
			FRotator Rotation = GetActorRotation();
			HookThatWasShoot = World->SpawnActor<AGrapplehook>(GrapplehookBlueprint, Location, Rotation);

			Cast<AGrapplehook>(HookThatWasShoot)->PlayerThatShoot = this;
		}
	}
	
}

void AMainPlayer::AlternateShoot()
{
	/*if (!bShooting)
	{
		bShooting = true;

		UWorld* World = GetWorld();
		if (World)
		{
			FVector Location = GetActorLocation() + GetActorForwardVector() * 100.f;
			FRotator Rotation = GetActorRotation();
			HookThatWasShoot = World->SpawnActor<AGrapplehook>(GrapplehookBlueprint, Location, Rotation);

			Cast<AGrapplehook>(HookThatWasShoot)->PlayerThatShoot = this;
		}
	}*/
}

void AMainPlayer::SetWalkingSpeed(float InWalkingSpeed)
{
	WalkingSpeed = InWalkingSpeed;
}

void AMainPlayer::LaunchPlayer()
{
	GetWorld()->GetFirstPlayerController()->GetCharacter()->LaunchCharacter(((Hit.GetActor()->GetActorLocation() - StartLineTrace) * 1.2f + FVector(0.f, 0.f, 350.f)), false, false);
}

void AMainPlayer::LaunchPlayerTest()
{
	GetWorld()->GetFirstPlayerController()->GetCharacter()->LaunchCharacter(((Hit.GetActor()->GetActorLocation() - StartLineTrace) * 1.2f + FVector(0.f, 0.f, 350.f)), false, false);
}

