// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MainExitDoor.generated.h"

UCLASS()
class PUZZLEGAME_API AMainExitDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainExitDoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		bool RunAnimationOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* SkeletalComponent;

	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
