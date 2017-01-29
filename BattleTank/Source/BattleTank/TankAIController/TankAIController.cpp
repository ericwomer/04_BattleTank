// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() 
{
  Super::BeginPlay();
  ATank* ControlledTank = GetControlledTank();
  
  if(ControlledTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s is the AI controlled tank."), *ControlledTank->GetName())
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to aquire AI contrlled tank."))
  }
}


