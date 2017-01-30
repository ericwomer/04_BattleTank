// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
  Super::BeginPlay();
  ATank* ControlledTank = GetControlledTank();
  
  if(ControlledTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s is the player controlled tank."), *ControlledTank->GetName())
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to aquire player contrlled tank."))
  }
}

void ATankPlayerController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  
  AimTowardsCrosshair();
    
}

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
  if(!GetControlledTank()) { return; }
  
  FVector HitLocation;
  if(GetSightRayHitLocation(HitLocation))
  {
    GetControlledTank()->GetTankAimingComponent()->AimAt(HitLocation);
  }
  
  // Get world location if linetrace trough crosshair.
  // If it hits landscape
    // tell controlled tank to aim at this point(?)
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
  // Find/Set crosshair location
  int32 viewportSizeX, viewportSizeY;
  
  GetViewportSize(viewportSizeX, viewportSizeY);
  FVector2D CrossHairScreenLocation = FVector2D(viewportSizeX * CrossHairXLocation, viewportSizeY * CrossHairYLocation);
  FVector LookDirection;
  FVector HitResultLocation;
  
  if (GetLookDirection(CrossHairScreenLocation, LookDirection))
  {
    // Everything working fine, return true.
    
    // Line-trace along that look direction, and see what we hit (up to the max rannge)
    GetLookVectorHitLocation(LookDirection, HitLocation);    
  }
  return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
  // "De-project" the screen position of the crosshair to a world direction
  FVector WorldCameraLocation; // To be discarded.
  return DeprojectScreenPositionToWorld( 
    ScreenLocation.X,
    ScreenLocation.Y,
    WorldCameraLocation,
    LookDirection
  );
  
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
  FHitResult HitResult;
  FVector StartLocation = PlayerCameraManager->GetCameraLocation();  
  FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
  
  if(GetWorld()->LineTraceSingleByChannel(
    HitResult, 
    StartLocation, 
    EndLocation, 
    ECollisionChannel::ECC_Visibility
    ))
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
 return false;
}

// UE_LOG(LogTemp, Warning, TEXT("HitResult Actor: %s"), *(HitResult.GetActor()->GetName()))

/*      DrawDebugLine(
        GetWorld(),
        StartLocation,
        EndLocation,
        FColor(255, 0, 0),
        false, -1, 0,
        10.0f);*/
