// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankBarrel.h"
#include "Ammo/Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!
}
