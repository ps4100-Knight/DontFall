// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "Engine/World.h"
#include "Components/PointLightComponent.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	// ...
}

void UInteractor::Interaction(AActor*& HitActor)
{
	FVector Start = GetComponentLocation();
	FVector End	= Start + GetForwardVector() * MaxDistance;
//	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape Sphear = FCollisionShape::MakeSphere(InteractRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, Sphear);

	if(HasHit)
	{
		
		HitActor = HitResult.GetActor();
		//TArray<UActorComponent*> lights = HitActor->GetComponentsByTag(UPointLightComponent::StaticClass(),"Light");
		

		//UE_LOG(LogTemp, Display, TEXT("The hit actor is %s"), *HitActor->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No hit"));
	}
}

