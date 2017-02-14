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


protected:

  UPROPERTY(BlueprintReadOnly, Category = "Tank - State")
  EFiringState FiringState = EFiringState::Reloading;
  

	// Called when the game starts
	virtual void BeginPlay() override;
  
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
  
  // ??
  UFUNCTION(BlueprintCallable, Category = "Tank - Fire")
  void Fire();
  
  UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  void Initalise(UTankTurret* InTurret, UTankBarrel* InBarrel);
  
  void AimAt(FVector HitLocation);
  
private:
	// Sets default values for this component's properties
	UTankAimingComponent();
  
  // ??
  UPROPERTY(EditAnywhere, Category = "Tank - Firing")
  float LaunchSpeed = 100000; // TODO: Find selseable value
  
  UTankBarrel* Barrel = nullptr;
  UTankTurret* Turret = nullptr;
  
  // ??
  UPROPERTY(EditDefaultsOnly, Category = "Tank - Setup")
  TSubclassOf<AProjectile> ProjectileBlueprint; // TODO[Done?]: Switch to TSubclassOf<> later
  
  // ??
  UPROPERTY(EditDefaultsOnly, Category = "Tank - Firing")
  float ReloadTimeInSeconds = 3.0f;
  
  // ??
  double LastFireTime = 0;
  
  void MoveBarrelTowards(FVector AimDirection);
  void MoveTurretTowards(FVector AimDirection);
	
};
