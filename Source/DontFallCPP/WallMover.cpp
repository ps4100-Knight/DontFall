// Fill out your copyright notice in the Description page of Project Settings.


#include "WallMover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UWallMover::UWallMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWallMover::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetOwner()->GetActorLocation();
	// ...
	
}


// Called every frame
void UWallMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for(ASwitch* Switch : Buttons)
	{
		if(Switch->IsActivated)
		{
			ShouldMove = true;
		}
		else
		{
			ShouldMove = false;
		}
	}

	if(ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = StartPosition + MoveOffset;
		float Speed = FVector::Distance(StartPosition, TargetLocation) / MoveTime;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation , TargetLocation , DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}
	// ...
}

