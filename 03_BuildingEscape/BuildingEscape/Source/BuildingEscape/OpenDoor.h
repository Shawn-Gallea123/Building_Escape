// Copyright Shawn Gallea 2017

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	void OpenDoor();
	void CloseDoor();
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -140.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;

	AActor *Owner; // owning Door

	float GetTotalMassOfActorsOnPlate();
	
};
