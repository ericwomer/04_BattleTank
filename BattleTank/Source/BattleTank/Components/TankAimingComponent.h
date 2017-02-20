// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
  Reloading,
  Aiming,
  Locked
};

// Forward declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Holds barrel's porperties and elevate
UCLASS( ClassGroup=(BattleTank), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
  UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  void Initalise(UTankTurret* InTurret, UTankBarrel* InBarrel);
  
  UFUNCTION(BlueprintCallable, Category = "Tank - Firing")
	void Fire();
  
  void AimAt(FVector HitLocation);
  
protected:
  UPROPERTY(BlueprintReadOnly, Category = "Tank - State")
  EFiringState FiringState = EFiringState::Reloading;
  
private:

  UPROPERTY(EditDefaultsOnly, Category = "Tank - Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Tank - Firing")
	float ReloadTimeInSeconds = 3;

  UPROPERTY(EditDefaultsOnly, Category = "Tank - Firing")
	float LaunchSpeed = 4000;
  
	double LastFireTime = 0;
	// Sets default values for this component's properties
  
  UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
  
  UTankAimingComponent();
    
  void MoveBarrelTowards(FVector AimDirection);
	
};
