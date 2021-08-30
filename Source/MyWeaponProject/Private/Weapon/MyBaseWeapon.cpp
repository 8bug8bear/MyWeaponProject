
#include "Weapon/MyBaseWeapon.h"

// Sets default values
AMyBaseWeapon::AMyBaseWeapon()
{
	bReplicates = true;

	//creating and joining scen componenta
	SC = CreateDefaultSubobject<USceneComponent>(TEXT("ScenComponent"));
	RootComponent = SC;
	//creating and joining weapon mesh 
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	//creating and joining muzzle
	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(WeaponMesh);

	bCanUse = true;
	bIsUsed = false;
}

//void AActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
//{
//	
//}

//interact function

void AMyBaseWeapon::Use() {}
void AMyBaseWeapon::StopUse() {}
void AMyBaseWeapon::AltUse() {}
void AMyBaseWeapon::StopAltUse() {}
void AMyBaseWeapon::Reload() {}


void AMyBaseWeapon::AtDeath() {}

void AMyBaseWeapon::ApplyUseDelay()
{
	bCanUse = false;
	bIsUsed = true;
	GetWorld()->GetTimerManager().SetTimer(timeUseDelay, this, &AMyBaseWeapon::SetCanUseInTrue, useRate, false);
}

void AMyBaseWeapon::SetCanUseInTrue()
{
	bCanUse = true;
}


// Called when the game starts or when spawned
void AMyBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}