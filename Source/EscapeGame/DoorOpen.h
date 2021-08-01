// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Set Time For Door To Remain Open 
	UPROPERTY(EditAnywhere,Category="DoorProperties")
		float DoorOpenTime = 2;

	//Collision Box To Place Objects  
    UPROPERTY(EditAnywhere,Category="DoorProperties")
		ATriggerVolume* PressurePlate = nullptr;	

	//Weight Require To Open Door
	UPROPERTY(EditAnywhere,Category="DoorProperties")
		float TriggerWeight=50;

	//Door Open Func
	void OpenDoor() const;
	//Door CLose FUnc
	void DoorClose() const;
	//Return Total Mass of Actors Overlapping Trigger Space
	float GetWeightOfActorsOverlapping() const;

	//Reference To Self;
	AActor* Door;		

};
