// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankTracks.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initalise(UTankTracks* Left, UTankTracks* Right)
{
  if(!Left || !Right) {return;}
  LeftTrack = Left;
  RightTrack = Right;
  
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{

  auto Time = GetWorld()->GetTimeSeconds();
  auto OwnerName = GetOwner()->GetName();
  auto Name = GetName();
  UE_LOG(LogTemp, Warning, TEXT("%f: %s of %s intends to move at a rate of %f!"), Time, *Name, *OwnerName, Throw)
 
  // Todo: Clamp actual throttle
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}
  

