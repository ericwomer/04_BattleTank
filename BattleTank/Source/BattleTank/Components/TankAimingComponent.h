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

// Holds barrel's porperties and elevate
UCLASS( ClassGroup=(BattleTank), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:

  UPROPERTY(BlueprintReadOnly, Category = "Tank - State")
  EFiringState FiringState = EFiringState::Reloading;
  
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
  
  void AimAt(FVector HitLocation, float LaunchSpeed);
  
  void SetBarrelReference( UTankBarrel* BarrelToSet);
  void SetTurretReference( UTankTurret* TurretToSet);
  
private:

  UTankBarrel* Barrel = nullptr;
  UTankTurret* Turret = nullptr;
  
  void MoveBarrelTowards(FVector AimDirection);
  void MoveTurretTowards(FVector AimDirection);
	
};
