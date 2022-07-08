
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "MyInterfaces/CharacterInterface.h"
#include "MyBaseWeapon.generated.h"

UCLASS()
class MYWEAPONPROJECT_API AMyBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMyBaseWeapon();

	//interact function
	UFUNCTION(BlueprintCallable, Category = "interact")
		virtual void Use();
	UFUNCTION(BlueprintCallable, Category = "interact")
		virtual void StopUse();
	UFUNCTION(BlueprintCallable, Category = "interact")
		virtual void AltUse();
	UFUNCTION(BlueprintCallable, Category = "interact")
		virtual void StopAltUse();
	UFUNCTION(BlueprintCallable, Category = "interact")
		virtual void Reload();

	virtual void AtDeath();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void ApplyUseDelay();
	UFUNCTION()
	void SetCanUseInTrue();
public:
	//Variable
	//Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SC;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere)
		UArrowComponent* Muzzle;

	UPROPERTY(BlueprintReadWrite, Category = "Ñharacter ")
		ACharacter* CharRef;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		FName attachSktName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
		FName detachSktName;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float useRate;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float minDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float maxDamage;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Fire")
		bool bCanUse;
	bool bIsUsed;
	FTimerHandle timeUseDelay;
};
