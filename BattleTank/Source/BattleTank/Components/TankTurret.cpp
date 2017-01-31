// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void  UTankTurret::Rotate( float ReletiveSpeed )
{
  ReletiveSpeed = FMath::Clamp(ReletiveSpeed, -1.0f, 1.0f);
  
  auto RotationChange = ReletiveSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
  auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

  SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
  
