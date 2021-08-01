#include "DoorOpen.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game
	// starts, and to be ticked every frame.You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDoorOpen::BeginPlay()
{
	
	Super::BeginPlay();
	
	//Owner Whom  Script Is Attached
	//Reference to Self 
	Door = GetOwner();
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    float LastDoorTime = 0;

	//Check Every Frame  Whether Colliding Actors Have Sufficient Weight
    if (GetWeightOfActorsOverlapping()>= TriggerWeight)
	{
		OpenDoor();
    	// Time Spent After Entering Play Mode  	
		LastDoorTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		DoorClose();
	}
     
	//Close Door After Short Delay 
	if (GetWorld()->GetTimeSeconds() - LastDoorTime > DoorOpenTime)
	{
		DoorClose();
	}
	else
	{
		UE_LOG(LogTemp,Display,TEXT("Door Still Open"));
	}	
}

void UDoorOpen::OpenDoor() const
{
	//Apply the rotation for open
	//This Apply on Attached Actor
	Door->SetActorRotation(FRotator(0, -90, 0));
}

void UDoorOpen::DoorClose() const
{
	//Apply the rotation for close
	//This Apply on Attached Actor
	Door->SetActorRotation(FRotator(0, 0, 0));
}

float UDoorOpen::GetWeightOfActorsOverlapping() const
{
	//Array Of Colliding Components
	TArray<UPrimitiveComponent*> OverlappingActors;
    PressurePlate->GetOverlappingComponents(OverlappingActors);

	//Final Total Mass Of Colliding Actors
	float TotalMassOfCollidingComponents =0; 

	//Cycle Through All The Colliding Actors
	for(int i=0;i<OverlappingActors.Num();i++)
	{
		//Get Mass Of Each Colliding Actor and Add Them Together
		TotalMassOfCollidingComponents+=OverlappingActors[i]->GetMass();
	}
	
	return TotalMassOfCollidingComponents;
}


