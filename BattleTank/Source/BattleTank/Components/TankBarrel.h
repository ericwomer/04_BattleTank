// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(BattleTank), meta=( BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  // -1 is max downward movement, +1 is max upward movement
  void Elevate( float ReletiveSpeed);
	
private:
  
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MaxDegreesPerSecond = 10.0f; // Sensible default MaxDegreesPerSecond
  
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MaxElevationDegrees = 40.0f; // Sensible default MaxElevation of barrel
  
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MinElevationDegrees = 0.0f; // Sensible default MinElevation of barrel
  
};
