// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankAimingComponent.h"
#include "Components/TankBarrel.h"
#include "Components/TankTurret.h"
#include "Ammo/Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  // No need to protect pointers in contructor
  TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  if(!BarrelToSet) { return; }
  TankAimingComponent->SetBarrelReference(BarrelToSet);
  Barrel = BarrelToSet;
  
}

void ATank::SetTurretReference( UTankTurret* TurretToSet)
{
  if(!TurretToSet) { return; }
  TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
  if (!Barrel) { return; }
  
  // Spawn a projectile at the socket location
  FVector NewLocation = Barrel->GetSocketLocation(FName("Projectile"));
  FRotator NewRotation = Barrel->GetSocketRotation(FName("Projectile"));
  
  auto Projectile = GetWorld()->SpawnActor<AProjectile>(
    ProjectileBlueprint,
    NewLocation,
    NewRotation
  );
  
  Projectile->LaunchProjectile(LaunchSpeed);
}

void ATank::AimAt(FVector HitLocation)
{
  TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

