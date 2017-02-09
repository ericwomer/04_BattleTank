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
  // Todo: Clamp actual throttle
  if(!LeftTrack || !RightTrack) {return;}
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
  // Todo: Clamp actual throttle
  if(!LeftTrack || !RightTrack) {return;}
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  
  auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();
  
  auto VDP = FVector::DotProduct(TankForward, AIForwardIntention);
  
  IntendMoveForward(VDP);
  // UE_LOG(LogTemp, Warning, TEXT("%f: %s of %s intends to move at a velocity of %s"), Time, *Name, *OwnerName, *MoveVelocity.GetSafeNormal().ToString())
  
}

/*  auto Time = GetWorld()->GetTimeSeconds();
  auto OwnerName = GetOwner()->GetName();
  auto Name = GetName();
  UE_LOG(LogTemp, Warning, TEXT("%f: %s of %s intends to move at a rate of %f!"), Time, *Name, *OwnerName, Throw)
 */
