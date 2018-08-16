// Fill out your copyright notice in the Description page of Project Settings.

#include "openDoor.h"

#define OUT

// Sets default values for this component's properties
UopenDoor::UopenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UopenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	if (!PressurePlate)
	{
		
		UE_LOG(LogTemp, Error, TEXT("missing presure plate"));
	}

	
}


// Called every frame
void UopenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (TotalMassOnPlate()== TriggerMass)
	{
		
		OpenRequest.Broadcast();
	}

	else
	{
		CloseRequest.Broadcast();
	}
}

float UopenDoor::TotalMassOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverLappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverLappingActors);
	for (const auto* Actor : OverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
		
	}
	return TotalMass;
}

