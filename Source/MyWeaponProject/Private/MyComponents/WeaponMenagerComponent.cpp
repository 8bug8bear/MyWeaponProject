// Fill out your copyright notice in the Description page of Project Settings.

#include "MyComponents/WeaponMenagerComponent.h"
#include "Math/Rotator.h"


// Sets default values for this component's properties
UWeaponMenagerComponent::UWeaponMenagerComponent(){}


void UWeaponMenagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponMenagerComponent, WeaponUsed);
	DOREPLIFETIME(UWeaponMenagerComponent, firstWeapon);
	DOREPLIFETIME(UWeaponMenagerComponent, secondWeapon);
}

// Called when the game starts
void UWeaponMenagerComponent::BeginPlay()
{
	Super::BeginPlay();

	CharRef = Cast<ACharacter>(GetOwner());
    
	if (GetOwnerRole() == ROLE_Authority)                                      // GetOwnerRole() == ROLE_Authority, GetWorld()->GetNetMode() != NM_Client, GetWorld()->IsServer()
	{
		if (CharRef)
		{
			GetWorld()->GetTimerManager().SetTimer(SpawnDel, this, &UWeaponMenagerComponent::CreateWeapon, 5.0f, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OwnerNotCharacter \n"));
		}
	}
}

void UWeaponMenagerComponent::CreateWeapon()
{
	FVector spawnLocation = CharRef->GetRootComponent()->GetComponentLocation();

	FRotator spawnRotation = CharRef->GetRootComponent()->GetComponentRotation();

	FActorSpawnParameters localSpawnParametrs;

	localSpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (!firstWeapon)
	{
		firstWeapon = GetWorld()->SpawnActor<AMyBaseWeapon>(FirstWeaponClass, spawnLocation, spawnRotation, localSpawnParametrs);

		FAttachmentTransformRules transformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

		firstWeapon->CharRef = CharRef;

		AttachWeapon(firstWeapon);
	}
	else
	{
		secondWeapon = GetWorld()->SpawnActor<AMyBaseWeapon>(FirstWeaponClass, spawnLocation, spawnRotation, localSpawnParametrs);

		FAttachmentTransformRules transformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);

		secondWeapon->CharRef = CharRef;

		AttachWeapon(secondWeapon);
	}
}

void UWeaponMenagerComponent::AttachWeapon_Implementation(AMyBaseWeapon* LWeapon)
{
	FAttachmentTransformRules transformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	LWeapon->AttachToComponent(Cast<ICharacterInterface>(CharRef)->GetGameMesh(), transformRules, LWeapon->attachSktName);
	/*GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("Attach weapon /n"));
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,CharRef->GetName() );*/
	WeaponUsed = LWeapon;
}

void UWeaponMenagerComponent::UseWeapon_Implementation()
{
	if (WeaponUsed)
	{
		WeaponUsed->Use();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponUsed not valid \n"));
	}
}

void UWeaponMenagerComponent::StopUseWeapon_Implementation()
{
	if (WeaponUsed)
	{
		WeaponUsed->StopUse();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponUsed not valid \n"));
	}
}

void UWeaponMenagerComponent::ReloadWeapon_Implementation()
{
	if (WeaponUsed)
	{
		WeaponUsed->Reload();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WeaponUsed not valid \n"));
	}
}



