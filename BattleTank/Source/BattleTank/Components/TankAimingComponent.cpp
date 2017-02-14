// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankBarrel.h"
#include "Components/TankTurret.h"
#include "Ammo/Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::Fire()
{
  bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
  
  if (Barrel && bIsReloaded) 
  { 
    // Spawn a projectile at the socket location
    FVector NewLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator NewRotation = Barrel->GetSocketRotation(FName("Projectile"));
    
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
      ProjectileBlueprint,
      NewLocation,
      NewRotation
    );
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Initalise(UTankTurret* InTurret, UTankBarrel* InBarrel)
{
  if(!InTurret || !InBarrel) { return; }
  Turret = InTurret;
  Barrel = InBarrel;
}

//
void UTankAimingComponent::AimAt(FVector HitLocation)
{
  if(!Barrel) { return; }
  
  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
  
  bool bHighArc = false;
  float CollisionRadious = 0.0f;
  float OverrideGravatiyZ = 0.0;
  
  // Caculate the OutLaunchVelocity
  bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
    this,
    OutLaunchVelocity,
    StartLocation,
    HitLocation,
    LaunchSpeed,
    false,
    0,
    0,
    ESuggestProjVelocityTraceOption::DoNotTrace
  );
  
  // Test to see if we have a hit solution.
  if(bHasAimSolution)
  {
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
    // MoveTurretTowards(AimDirection);
    // auto Time = GetWorld()->GetTimeSeconds();
    // UE_LOG(LogTemp, Warning, TEXT("%f: Should be false?"), Time)
  }
  else
  {
    auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: No Aiming Solution Found!"), Time)
  }
  
/// BEGIN: Do not delete bellow this line
//  TArray<AActor*>  ActorsToIgnore;
//  bool bDebugTrace = false;
//  if(UGameplayStatics::SuggestProjectileVelocity(
//      this,
//      OutLaunchVelocity,
//      StartLocation,
//      HitLocation,
//      LaunchSpeed,
//      bHighArc,
//      CollisionRadious,
//      OverrideGravatiyZ,
//      ESuggestProjVelocityTraceOption::TraceFullPath,
//      FCollisionResponseParams::DefaultResponseParam,
//      ActorsToIgnore,
//      bDebugTrace
//    ))
//  {
//    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
//    UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString())
//  }
/// END: Do not delete bellow this line

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  if(!Barrel || !Turret) { return; }
  // Work out difference between current barrel rotation and AimDirection
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotation = AimDirection.Rotation();
  FRotator DeltaRotation = AimAsRotation - BarrelRotator;
  
  Turret->Rotate(DeltaRotation.Yaw);
  Barrel->Elevate(DeltaRotation.Pitch);
  
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
  // Work out difference between current barrel rotation and AimDirection
  FRotator TurretRotator = Turret->GetUpVector().Rotation(); // Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotation = AimDirection.Rotation();
  FRotator DeltaRotation = AimAsRotation - TurretRotator;
  
  Turret->Rotate(DeltaRotation.Yaw);
}


