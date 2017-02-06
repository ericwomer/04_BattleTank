// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

/// TODO: Split up barrel and elevator component into seperate objects later so 
/// it will beable to animate barrel coil later on.

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
  UTankAimingComponent* GetTankAimingComponent() { return TankAimingComponent; }
  
	// Sets default values for this pawn's properties
	ATank();
    
  UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  void SetBarrelReference( UTankBarrel* BarrelToSet);
  
  UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  void SetTurretReference( UTankTurret* TurretToSet);
  
  UFUNCTION(BlueprintCallable, Category = "Tank - Firing")
  void Fire();
  
  void AimAt(FVector HitLocation);
  
protected:

  UTankAimingComponent* TankAimingComponent = nullptr;
  
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
  UPROPERTY(EditDefaultsOnly, Category = "Tank - Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint; // TODO[Done?]: Switch to TSubclassOf<> later
    
  UPROPERTY(EditAnywhere, Category = "Tank - Firing")
  float LaunchSpeed = 100000; // TODO: Find selseable value
  
  UPROPERTY(EditDefaultsOnly, Category = "Tank - Firing")
  float ReloadTimeInSeconds = 3.0f;
  
  // Local barrel reference
  UTankBarrel* Barrel = nullptr;
  
  double LastFireTime = 0;
  
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  
};
