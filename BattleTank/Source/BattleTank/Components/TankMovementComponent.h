// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTracks;

/**
 * Responseable for driving the tank tracks
 */
UCLASS( ClassGroup=(BattleTank), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

  UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  void Initalise(UTankTracks* Left, UTankTracks* Right);


  UFUNCTION(BlueprintCallable, Category = TankInput)
	void IntendMoveForward(float Throw);
	
private:
  UTankTracks* LeftTrack = nullptr;
  UTankTracks* RightTrack = nullptr;
	
};
