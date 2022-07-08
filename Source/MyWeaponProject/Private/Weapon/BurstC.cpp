// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BurstC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

ABurstC::ABurstC()
{
	fireComponent = CreateDefaultSubobject<ULineTraceFireComponent>(TEXT("fireComponent"));
	burstShotsAmount = 0;
	PrimaryActorTick.bCanEverTick = true;
}


void ABurstC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, TEXT("Helth:"));
}

void ABurstC::Use()
{
	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, TEXT("Helth:"));
	GetWorld()->GetTimerManager().SetTimer(burstTime, this, &ABurstC::fireBurst, fireDelay, false);

}

void ABurstC::StopUse()
{
	if (bIsUsed)
	{
		GetWorldTimerManager().ClearTimer(burstTime);
	}

}

void ABurstC::AtDeath()
{
	GetWorldTimerManager().ClearTimer(burstTime);
	GetWorldTimerManager().ClearTimer(burstHandle);
}

void ABurstC::fireBurst()
{
	
		ApplyUseDelay();
		GetWorld()->GetTimerManager().SetTimer(burstHandle, this, &ABurstC::bursting, burstRate, true);
	
}

void ABurstC::bursting()
{
	if (burstShotsAmount < numberBurstShots)
	{
		if (ICharacterInterface* LocalCharref = Cast<ICharacterInterface>(CharRef))
		{
			FVector lokalStart = LocalCharref->GetCameraRef()->GetComponentLocation();

			FVector lokalForvard = UKismetMathLibrary::GetForwardVector(LocalCharref->GetCameraRef()->GetComponentRotation());

			float localDamage = FMath::RandRange(minDamage, maxDamage);

			fireComponent->Fire(lokalStart, lokalForvard, Muzzle->GetComponentLocation(), CharRef, localDamage, damageAlpha, aimAssist);

			burstShotsAmount++;
		}
	}
	else
	{

		GetWorldTimerManager().ClearTimer(burstHandle);
		burstShotsAmount = 0;
	}
}



