// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankBarrel.h"
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


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
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
    ESuggestProjVelocityTraceOption::DoNotTrace
  );
  
  // Test to see if we have a hit solution.
  if(bHasAimSolution)
  {
    auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
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

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  if(!BarrelToSet) { return; }
  Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  // Work out difference between current barrel rotation and AimDirection
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotation = AimDirection.Rotation();
  FRotator DeltaRotation = AimAsRotation - BarrelRotator;
  
  Barrel->Elevate(5);
}
