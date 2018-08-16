// Fill out your copyright notice in the Description page of Project Settings.

#include "positionreporter.h"
#include "EscapeHouse.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values for this component's properties
Upositionreporter::Upositionreporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Upositionreporter::BeginPlay()
{
	Super::BeginPlay();

	FString objectName = GetOwner()->GetName();
	FString objectPos = GetOwner()->GetActorLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT(" %s, is at %s"), *objectName, *objectPos);

	
}


// Called every frame
void Upositionreporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

