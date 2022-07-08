// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MyBaseWeapon.h"
#include "MyComponents/LineTraceFireComponent.h"
#include "BurstC.generated.h"

/**
 * 
 */
UCLASS()
class MYWEAPONPROJECT_API ABurstC : public AMyBaseWeapon
{
	GENERATED_BODY()

public:
	ABurstC();

	virtual void Tick(float DeltaTime) override;

	void Use() override;

	void StopUse() override;

	void AtDeath() override;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float fireDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float burstRate;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		int numberBurstShots;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float damageAlpha;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float aimAssist;


	ULineTraceFireComponent* fireComponent;
private:
	FTimerHandle burstTime;

	FTimerHandle burstHandle;

	int burstShotsAmount;

	void fireBurst();

	void bursting();
};
