// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"

// Sets the throttal between 1 and -1
void UTankTracks::SetTrottle(float Throttle)
{
  auto Time = GetWorld()->GetTimeSeconds();
  auto Name = GetOwner()->GetName();
  auto LocalName = GetName();
  UE_LOG(LogTemp, Warning, TEXT("%f: %s throttle of %s is at %f!"), Time, *Name, *LocalName, Throttle)
  
  // Todo: Clamp actual throttle
  // Todo: Key Arrows controlling throttle don't really work right now.
  auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
  auto ForceLocation = GetComponentLocation();
  
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
  
}
