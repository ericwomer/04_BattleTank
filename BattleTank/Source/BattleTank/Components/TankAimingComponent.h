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
  
  void AimAt(FVector HitLocation, float LaunchSpeed);
  
protected:
  UPROPERTY(BlueprintReadOnly, Category = "Tank - State")
  EFiringState FiringState = EFiringState::Reloading;
  
private:
	// Sets default values for this component's properties
	UTankAimingComponent();
  
  UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
  
  void MoveBarrelTowards(FVector AimDirection);
	
};
