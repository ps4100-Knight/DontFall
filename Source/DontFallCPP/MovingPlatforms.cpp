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
}

// Called every frame
void AMovingPlatforms::Tick(float DeltaTime)
{
	MovePlatform(DeltaTime);	
	RotatePlatform(DeltaTime);	

}

void AMovingPlatforms::MovePlatform(float DeltaTime)
{
	if(ShouldReturn())
	{
		FVector moveDirection = platformVelocity.GetSafeNormal();		//find out the direction of movement based on velocity vector
		startLocation = startLocation + moveDirection * moveDistance;	//change the start location to the new location (end of movement)
		SetActorLocation(startLocation);								//set the location to that point to deal with any overshoot
		platformVelocity = -platformVelocity;							//reverse the velocity to start moving in other direction
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
	FRotator currentRotation = GetActorRotation();						//get current rotation
	currentRotation += platformRotation * DeltaTime;					//next rotation state
	SetActorRotation(currentRotation);									//rotate
}

bool AMovingPlatforms::ShouldReturn() const
{
	return (GetDistanceMoved() > moveDistance);
}
float AMovingPlatforms::GetDistanceMoved() const
{
	return FVector::Dist(startLocation, GetActorLocation());
}



