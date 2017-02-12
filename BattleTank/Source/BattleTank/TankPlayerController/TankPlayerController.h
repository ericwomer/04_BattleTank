// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
  
  UFUNCTION(BlueprintCallable, Category = "Tank - Setup")
  ATank* GetControlledTank() const;
  
private:
  
  UPROPERTY(EditDefaultsOnly)
  float CrossHairXLocation = 0.5f;
    
  UPROPERTY(EditDefaultsOnly)
  float CrossHairYLocation = 0.3333f;
  
  UPROPERTY(EditDefaultsOnly)
  float LineTraceRange = 1000000; // I assume in cm if not convert to M or KM.
    
  virtual void BeginPlay() override;
  virtual void Tick( float DeltaTime ) override;
  
 
  
	void AimTowardsCrosshair();
  bool GetSightRayHitLocation(FVector& HitLocation) const;
  bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
  bool GetLookVectorHitLocation(FVector LookDirection,  FVector& HitLocation) const;
    
};
