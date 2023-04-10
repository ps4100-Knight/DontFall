// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatforms.h"

// Sets default values
AMovingPlatforms::AMovingPlatforms()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();	//store the start location for later use
	startRotation = GetActorRotation(); //store the start rotation for later use
	startRotation.Roll = int32(startRotation.Roll);
	startRotation.Pitch = int32(startRotation.Pitch);
	startRotation.Yaw = int32(startRotation.Yaw);
}

// Called every frame
void AMovingPlatforms::Tick(float DeltaTime)
{
	MovePlatform(DeltaTime);	
	RotatePlatform(DeltaTime);	

}

void AMovingPlatforms::MovePlatform(float DeltaTime)
{
	if(ShouldReturn() && returns)
	{
		FVector moveDirection = platformVelocity.GetSafeNormal();		//find out the direction of movement based on velocity vector
		startLocation = startLocation + moveDirection * moveDistance;	//change the start location to the new location (end of movement)
		SetActorLocation(startLocation);								//set the location to that point to deal with any overshoot
		platformVelocity = -platformVelocity;							//reverse the velocity to start moving in other direction
	}
	else if (ShouldReturn() && !returns)
	{
		//do nothing
	}
	else
	{
		FVector currentLocation = GetActorLocation();					//get current location
		currentLocation += platformVelocity * DeltaTime;				//the next point of movement
		SetActorLocation(currentLocation);								//move there
	}
}

void AMovingPlatforms::RotatePlatform(float DeltaTime)
{
	//check if it should counter rotate
	//check if its rotated full 
	//if it has change the roation direction
	if (hasStartedRotating && HasMadeFullRotation())
	{
		platformRotation = platformRotation.GetInverse();
	}
	FRotator currentRotation = GetActorRotation();
	currentRotation += platformRotation * DeltaTime;
	/*if (displayDebug)
	{
		FString temp = currentRotation.ToString();
		UE_LOG(LogTemp, Display, TEXT("current rotation %s"), *temp);
	}*/
	SetActorRotation(currentRotation);
	hasStartedRotating = true;
}

bool AMovingPlatforms::ShouldReturn() const
{
	return (GetDistanceMoved() > moveDistance);
}
float AMovingPlatforms::GetDistanceMoved() const
{
	return FVector::Dist(startLocation, GetActorLocation());
}

bool AMovingPlatforms::HasMadeFullRotation() const
{
	FRotator temp = GetActorRotation();
	temp.Pitch = int32(temp.Pitch);
	temp.Yaw = int32(temp.Yaw);
	temp.Roll = int32(temp.Roll);
	return (temp == startRotation);
}



