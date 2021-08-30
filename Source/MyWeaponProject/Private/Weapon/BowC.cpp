// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BowC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

ABowC::ABowC()
{
	fireComponent = CreateDefaultSubobject<ULineTraceFireComponent>(TEXT("fireComponent"));
}

void ABowC::Use()
{
	if (bCanUse)
	{
		ApplyUseDelay();
		maxEnergi = false;
		fireRedy = true;
		GetWorld()->GetTimerManager().SetTimer(maxEnergyTime, this, &ABowC::setMaxEnergy, fireDelay, false);
	}
}

void ABowC::StopUse()
{
	//UE_LOG(LogTemp, Log, TEXT("StopUse in Bow. \n"));
	if (bIsUsed && fireRedy)
	{
		fireRedy = false;
		float timeElaps = GetWorld()->GetTimerManager().GetTimerElapsed(maxEnergyTime);
		if (timeElaps > 0.2f || timeElaps < 0.f)
		{
			
			float localDamage = FMath::RandRange(minDamage, maxDamage);
			if (!maxEnergi)
			{
				localDamage *= (timeElaps / fireDelay);
				//UE_LOG(LogTemp, Log, TEXT("Is not max energi. \n"));
			}
			if (ICharacterInterface* LocalCharref = Cast<ICharacterInterface>(CharRef))
			{
				FVector lokalStart = LocalCharref->GetCameraRef()->GetComponentLocation();

				FVector lokalForvard = UKismetMathLibrary::GetForwardVector(LocalCharref->GetCameraRef()->GetComponentRotation());

				fireComponent->Fire(lokalStart, lokalForvard, Muzzle->GetComponentLocation(), CharRef, localDamage, damageAlpha, aimAssist);

			}
			else 
			{
				UE_LOG(LogTemp, Warning, TEXT("Character heve not ICharacterInterface!"));
			}
		}
		else
		{
			GetWorldTimerManager().ClearTimer(maxEnergyTime);
		}
	}
}

void ABowC::Reload()
{
	fireRedy = false;
	GetWorldTimerManager().ClearTimer(maxEnergyTime);
}

void ABowC::AtDeath()
{
	GetWorldTimerManager().ClearTimer(maxEnergyTime);
}

void ABowC::setMaxEnergy() { maxEnergi = true; }



