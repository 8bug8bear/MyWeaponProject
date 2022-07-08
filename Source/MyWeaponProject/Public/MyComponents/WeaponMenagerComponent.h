#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/MyBaseWeapon.h"
#include "MyInterfaces/CharacterInterface.h"
#include "Net/UnrealNetwork.h"
#include "WeaponMenagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYWEAPONPROJECT_API UWeaponMenagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponMenagerComponent();
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
		void CreateWeapon();

	UFUNCTION(NetMulticast, Unreliable)
		void AttachWeapon(AMyBaseWeapon* LWeapon);


	UFUNCTION(Server, Unreliable)
		void UseWeapon();
	UFUNCTION(Server, Unreliable)
		void StopUseWeapon();
	UFUNCTION(Server, Unreliable)
		void ReloadWeapon();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AMyBaseWeapon> FirstWeaponClass;
	UPROPERTY(replicated)
	AMyBaseWeapon* WeaponUsed;
	UPROPERTY(replicated)
	AMyBaseWeapon* firstWeapon;
	UPROPERTY(replicated)
	AMyBaseWeapon* secondWeapon;

	ACharacter* CharRef;
	
	FTimerHandle SpawnDel;
};
