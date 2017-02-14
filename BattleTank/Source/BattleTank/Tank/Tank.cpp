// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Components/TankAimingComponent.h"
#include "Components/TankBarrel.h"
#include "Components/TankTurret.h"
#include "Components/TankMovementComponent.h"
#include "Ammo/Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
