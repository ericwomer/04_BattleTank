// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

/// TODO: Split up barrel and elevator component into seperate objects later so 
/// it will beable to animate barrel coil later on.
/// Add back in Hit and Fire?

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
  
  virtual void BeginPlay() override;
  
private:
    UTankMovementComponent* TankMovementComponent = nullptr;
    UTankAimingComponent* TankAimingComponent = nullptr;
    
  // Depricated - Will be removed with next refactor process 
  // UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  // void SetBarrelReference( UTankBarrel* BarrelToSet);
  
  // void AimAt(FVector InHitLocation);  
  
};
