// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandleSearch();
	SetUpInput();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		//UE_LOG(LogTemp,Warning,TEXT("componenet found"))
		PhysicsHandle->SetTargetLocation(GetDebugLineEnd());
	}

}

void UGrabber::PhysicsHandleSearch()
{
	// Search Physics Handle Component Attached To Owner

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	//Check Whether physics handle Attached or Not 
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Not Attached"));
	}
}


void UGrabber::SetUpInput()
{
	//Finding Input component script attached to the default pawn character(owner)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		//Action Mapping
		//
		//Binding Action For Grab and Release
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("input component missing "));
	}
}



FVector UGrabber::GetDebugLineStart() const
{

	//this is actual player location from the origin in vector form 
	FVector  PlayerLocation;

	//this is a rotator which gives the direction in which player is seeing 
	//but in the form of FRotator 
	FRotator PlayerRoation;


	//getting the values for playerLocation and Rotation by accessing player 
	//and than its ViewPoint 
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation,
		PlayerRoation
	);

	//converting the direction Rotator into a vector of desired length
	//than obtaining the resultant vector from location and direction 
	return PlayerLocation;
	
}

FVector UGrabber::GetDebugLineEnd() const
{
	FVector  PlayerLocation;
	FRotator PlayerRoation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation,
		PlayerRoation
	);
	return PlayerLocation + PlayerRoation.Vector() * ObjectDistance;
	
}


FHitResult UGrabber::GetFirstPhysicsBodyOnHit() const
{	
	//using the resultant vector to draw debug line to show the line trace in player 
	//params:start point,end point,color of line (RGB),redraw line at ever frame(persistence) 
	//life time,depth priority,thickness.

	//This Is For Visualisation Of Line Trace
	DrawDebugLine(GetWorld(),GetDebugLineStart(),GetDebugLineEnd(),
		FColor(0, 255, 0),false, 0, 0,10);


	FHitResult Hit;

	// Defining What To Ignore On Hit 
	//params:- FName,complex geometry,ignore
	FCollisionQueryParams MyQueryParama(FName(TEXT("")), false, GetOwner());

	//RayCast(LineTrace)
	//Selecting Colliding Object Based On Object Type 
	GetWorld()->LineTraceSingleByObjectType(Hit,
		GetDebugLineStart(),
		GetDebugLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		MyQueryParama);

    //Result From Line Trace Will Be Stored In Hit
	return Hit;
}

void UGrabber::Grab() 
{
	//Get The Hit Result From Line Trace 
	auto HitResult = GetFirstPhysicsBodyOnHit();
    //Get Component That Hit From Hit Result
	auto ComponentToGrab = HitResult.GetComponent();
    //Get the Actor Associated With The Component
	auto ActorHit = HitResult.GetActor();

	///Line trace and Try and reach any object that has physics body chanel set
	///If we hit something attach Physics body to Line Trace End 
	if (ActorHit != nullptr)
	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation()
		);
	}
}

void UGrabber::Release()
{
	//Release The Attached Physics Body
	PhysicsHandle->ReleaseComponent();
}


