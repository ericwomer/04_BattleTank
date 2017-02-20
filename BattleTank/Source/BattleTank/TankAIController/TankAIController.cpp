// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
  Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  
  auto ControlledTank = GetPawn();
  auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
  if(!ensure(PlayerTank && ControlledTank)) { return; }
    
  auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();  
  
  if(!ensure( AimingComponent)) { return; }
  
  FVector PlayerLocation = PlayerTank->GetActorLocation();
  
  MoveToActor(PlayerTank, AcceptanceRadius);
  AimingComponent->AimAt(PlayerLocation);
  
  // TODO: Implement Fire in aiming component
  AimingComponent->Fire(); // Todo: don't fire at every frame.
}


