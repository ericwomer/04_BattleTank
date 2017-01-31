// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TankAimingComponent.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
  // void AimAt(FVector HitLocation);
  UTankAimingComponent* GetTankAimingComponent() { return TankAimingComponent; }
  
  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetBarrelReference( UTankBarrel* BarrelToSet);
  
  void AimAt(FVector HitLocation);
  
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  
  UTankAimingComponent* TankAimingComponent = nullptr;
  
  UPROPERTY(EditAnywhere, Category = Firing)
  float LaunchSpeed = 100000; // TODO: Find selseable value
  
private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
