// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate( float ReletiveSpeed)
{
  // Move the barrel the right amount this frame
  // Given a max elevation speed, and the frame time
  
  ReletiveSpeed = FMath::Clamp(ReletiveSpeed, -1.0f, 1.0f);
  
  auto ElevationChange = ReletiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
  auto ClampedElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
  
  SetRelativeRotation(FRotator(ClampedElevation,0,0));
  
}

//  auto Time = GetWorld()->GetTimeSeconds();
//  UE_LOG(LogTemp, Warning, TEXT("%f: DegreesPerSecond: %f"), Time, ReletiveSpeed)

