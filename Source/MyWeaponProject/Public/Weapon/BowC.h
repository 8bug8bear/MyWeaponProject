// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MyBaseWeapon.h"
#include "MyComponents/LineTraceFireComponent.h"
#include "BowC.generated.h"

/**
 * 
 */
UCLASS()
class MYWEAPONPROJECT_API ABowC : public AMyBaseWeapon
{
	GENERATED_BODY()
	
public:
	ABowC();

	void Use() override;

	void StopUse() override;

	void Reload() override;

	void AtDeath() override;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float fireDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float damageAlpha;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float aimAssist;

	ULineTraceFireComponent* fireComponent;

private:
	UFUNCTION()
	void setMaxEnergy();
	bool maxEnergi;
	bool fireRedy;
	FTimerHandle maxEnergyTime;
};

