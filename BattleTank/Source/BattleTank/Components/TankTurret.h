// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(BattleTank), meta=( BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  
  // Rotate turret at a reletive speed
  void Rotate( float ReletiveSpeed );
	
private:
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MaxDegreesPerSecond = 25.0f; // TODO test: Sensible default MaxDegreesPerSecond
	
};
