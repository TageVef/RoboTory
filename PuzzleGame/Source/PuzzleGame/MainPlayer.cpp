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

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	
	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Box"));
	//CapsuleComponent->bGenerateOverlapEvents = true;
	//CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayer::OnOverlap);
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

		RotateTowardsMouse(DeltaTime, XPosition, YPosition);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting up Action bindings
	InputComponent->BindAction("Climb", IE_Pressed, this, &AMainPlayer::Climb);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainPlayer::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &AMainPlayer::Interact);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMainPlayer::Shoot);

	//Settign up Axis bindings
	InputComponent->BindAxis("MoveX", this, &AMainPlayer::MoveX);
	InputComponent->BindAxis("MoveY", this, &AMainPlayer::MoveY);


}

void AMainPlayer::MoveX(float AxisValue)
{
	AddMovementInput(FVector::ForwardVector, AxisValue);
	if (MovableObject && Holding)
	{
		Cast<AMovableObject>(MovableObject)->MoveObject(GetActorForwardVector() * WalkingSpeed);
	}
}

void AMainPlayer::MoveY(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);

		if (MovableObject && Holding)
		{
			Cast<AMovableObject>(MovableObject)->MoveObject(GetActorRightVector() * WalkingSpeed);
		}
}

void AMainPlayer::Climb()
{

}

void AMainPlayer::Interact()
{
	Holding = !Holding;
}

void AMainPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult &Sweepresult)
{
	if (OtherActor->IsA(AMovableObject::StaticClass()))
	{
		MovableObject = OtherActor;
	}
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
	UWorld* World = GetWorld();
	if (World)
	{
		// There is a problem somewhere, character is shooting from the right side, not the front side.
		// Probably something wrong in the RotateTowardsMouse() function.
		FVector Location = GetActorLocation() +(GetActorForwardVector() * 100.f);
		FRotator Rotation = GetActorRotation();

		World->SpawnActor<AGrapplehook>(GrapplehookBlueprint, Location, Rotation);
	}
	
}

