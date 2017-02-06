// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTraks is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS(  meta=( BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

  UFUNCTION(BlueprintCallable, Category = TankInput)
  void SetThrottle(float Throttle);
  
private:
  UPROPERTY(EditDefaultsOnly)
  float TrackMaxDrivingForce = 400000.0f;
	
};
