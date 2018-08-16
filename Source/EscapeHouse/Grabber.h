// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEHOUSE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	void Grab(); //ray-cast and grab physicsbody objects
	void Release();// release the object
	void FindPhysicsComp();//find physiccomponent from charracter_bp we must add first
	void InputCompEvents();//input events names must be same
	FVector GetLineEnd();
	FVector GetLineStart();

	const FHitResult GetObjectInReach();

	UPhysicsHandleComponent* handler = nullptr;
	UInputComponent* handlerInput = nullptr;

	float reach = 100.f;
	
};
