// Copyright Shawn Gallea 2017

#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// We will poll the TriggerVolume every frame
	if (GetTotalMassOfActorsOnPlate() > 30.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it's time to close the door

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("Missing Pressure Plate for %s"), *GetOwner()->GetName());
		return 1.f;
	}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them, adding their masses
	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}