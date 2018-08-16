// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Core/Public/Delegates/Delegate.h"
#include "openDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEHOUSE_API UopenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UopenDoor();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent CloseRequest;

	
private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

		AActor* owner = nullptr;


		float doorLastOpen;
		UPROPERTY(EditAnywhere)
		float TriggerMass = 700.f;
		float TotalMassOnPlate();
};
