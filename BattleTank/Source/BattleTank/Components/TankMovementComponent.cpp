// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankTracks.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initalise(UTankTracks* Left, UTankTracks* Right)
{
  if(!ensure(Left && Right)) {return;}
  LeftTrack = Left;
  RightTrack = Right;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
  if(!ensure(LeftTrack && RightTrack)) {return;}
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
  if(!ensure(LeftTrack && RightTrack)) {return;}
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
  auto AIForwardIntention = MoveVelocity.GetSafeNormal();
  
  auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
  IntendMoveForward(ForwardThrow);
  
  auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
  IntendMoveRight(RightThrow);
}

/*  auto Time = GetWorld()->GetTimeSeconds();
  auto OwnerName = GetOwner()->GetName();
  auto Name = GetName();
  UE_LOG(LogTemp, Warning, TEXT("%f: %s of %s intends to move at a rate of %f!"), Time, *Name, *OwnerName, Throw)
 */
