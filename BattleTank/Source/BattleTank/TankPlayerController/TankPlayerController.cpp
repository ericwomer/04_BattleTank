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
    // UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
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
  
  if (GetLookDirection(CrossHairScreenLocation, LookDirection))
  {
    // Everything working fine, return true.
    UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString())
    return true;
  }
  
  // Line-trace along that look direction, and see what we hit (up to the max rannge)
  
  HitLocation = FVector(1.0);
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
