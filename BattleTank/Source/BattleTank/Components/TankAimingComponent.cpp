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
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initalise(UTankTurret* InTurret, UTankBarrel* InBarrel)
{
  if(!ensure(InTurret && InBarrel)) { return; }
  Turret = InTurret;
  Barrel = InBarrel;
}

//
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
  if(!ensure(Barrel)) { return; }
  
  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
  
  bool bHighArc = false;
  float CollisionRadious = 0.0f;
  float OverrideGravatiyZ = 0.0;
  
  TArray<AActor*>  ActorsToIgnore;
  bool bDebugTrace = false;
  
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
    ESuggestProjVelocityTraceOption::DoNotTrace /*,
    FCollisionResponseParams::DefaultResponseParam, FCollisionResponseParams::
    ActorsToIgnore,
    bDebugTrace*/
  );
  
  // Test to see if we have a hit solution.
  if(bHasAimSolution)
  {
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
    // UE_LOG(LogTemp, Warning, TEXT("I am here!"))
  }
  /*else
  {
    auto Time = GetWorld()->GetTimeSeconds();
    auto OwnerName = GetOwner()->GetName();
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s of %s No Aiming Solution Found!"), Time, *Name, *OwnerName)
  }*/
  
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
  if(!ensure(Barrel && Turret)) { return; }
  // Work out difference between current barrel rotation and AimDirection
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotation = AimDirection.Rotation();
  FRotator DeltaRotation = AimAsRotation - BarrelRotator;
  
  Turret->Rotate(DeltaRotation.Yaw);
  Barrel->Elevate(DeltaRotation.Pitch);
  
}
