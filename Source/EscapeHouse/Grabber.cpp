// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsComp();
	InputCompEvents();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//add handler to reachable distance end
	if (!handler)
	{
		return;
	}
	if (handler->GrabbedComponent)
	{
		handler->SetTargetLocation(GetLineEnd());
	}
}

//grab the object
void UGrabber::Grab()
{
	
	auto HitResult = GetObjectInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	//if action hit physicbody component ready to run this code
	if (ActorHit)
	{
		if (!handler)
		{
			return;
		}
		handler->GrabComponent(
			ComponentToGrab,
			NAME_None, //no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true //allow to rotation
		);
	}
}
//release the object when up to mouse button
void UGrabber::Release() {
	if (!handler)
	{
		return;
	}
	handler->ReleaseComponent();
}

//finding physics handler in the character_bp if we don't add physics handler giving to error
void UGrabber::FindPhysicsComp()
{//physics handler
	handler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (handler == nullptr)
	{
     	UE_LOG(LogTemp, Error, TEXT("%s Missing physic handler"), *GetOwner()->GetName());
	}
}
//finding buttons to engine/inputs tab and binding actions and running functions name must be same
void UGrabber::InputCompEvents()
{
	//input comp actions
	handlerInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (handlerInput)
	{
		UE_LOG(LogTemp, Warning, TEXT("input comp. found"));
		handlerInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		handlerInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing input comp."), *GetOwner()->GetName());
	}
}
//getting line end for every tick
FVector UGrabber::GetLineEnd()
{
	//get character's reachable distance
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);
	return PlayerViewLocation + PlayerViewRotation.Vector()  * reach;	
}

FVector UGrabber::GetLineStart()
{
	//get character's reachable distance
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);
	return PlayerViewLocation;
}

//Making Ray-cast and setting up to work only on physicsbody
const FHitResult UGrabber::GetObjectInReach()
{
	///raycast setup
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetLineStart(),
		GetLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return HitResult;
}