// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UGrabber : public UActorComponent
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
	UPROPERTY(EditAnywhere)
		int ObjectDistance=50;

	//General Components to check for
	UPhysicsHandleComponent* PhysicsHandle=nullptr;
	UInputComponent* InputComponent = nullptr;

	
	//Search PhysicsHandle Component
	void PhysicsHandleSearch();
    
	//Search  Input Component Set up input for Grabbing
	void SetUpInput();

	//Task to do on Grab key pressed
	void Grab() ;

	//Task to do on Grab Key released
	void Release();

	//Get first physics body attached component
	FHitResult GetFirstPhysicsBodyOnHit() const;

	//Position Vector Determination Function 
	FVector GetDebugLineStart() const;
	FVector GetDebugLineEnd() const;

};
