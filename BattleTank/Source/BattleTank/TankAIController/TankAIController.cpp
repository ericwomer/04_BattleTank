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
  
  PlayerControlledTank = GetPlayerTank();
  if(PlayerControlledTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s is reporting that %s is the PlayerControlledTank"), *ControlledTank->GetName(), *PlayerControlledTank->GetName())
  }
  else 
  {
    UE_LOG(LogTemp, Error, TEXT("Could not get PlayerControlledTank for %s!"), *ControlledTank->GetName())
  }
  
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  
  AimTowardsPlayer();
    
}

ATank* ATankAIController::GetPlayerTank() const
{
  auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if(!PlayerPawn) { return nullptr;}
  return Cast<ATank>(PlayerPawn);
}

void ATankAIController::AimTowardsPlayer()
{
  
  GetControlledTank()->GetTankAimingComponent()->AimAt(GetPlayerTank()->GetActorLocation());
}
