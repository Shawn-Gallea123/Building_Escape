// Copyright Shawn Gallea 2017

#pragma once



#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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
	// how far we are reaching in cm
	float Reach = 100.f;
		
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();
	void Release();

	// Find attached physics handle
	void FindPhysicsHandleComponent();

	// Set up input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Returns the current start of reach line
	FVector GetReachLineStart();

	// Returns the current end of reach line
	FVector GetReachLineEnd();

};
