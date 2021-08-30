
#include "MyComponents/LineTraceFireComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULineTraceFireComponent::ULineTraceFireComponent()
{
	
}

bool ULineTraceFireComponent::Fire(FVector cameraWL, FVector cameraFW, FVector muzzleWL, AActor* ignore, float damage, float damageAlpha, float aimAsist)
{
	FHitResult result;

	FVector localStart = cameraWL + (cameraFW * 110.0f);
	FVector localEnd = cameraFW * 10000000.0f;

	FCollisionShape myColisionShape = FCollisionShape::MakeSphere(aimAsist);
	//Creating a list of ignored actors
	FCollisionQueryParams myColisionQP;
	myColisionQP.AddIgnoredActor(ignore);
	//Debug capsule trace by channel start
	DrawDebugSphere(GetWorld(), localStart, myColisionShape.GetSphereRadius(), 20, FColor::Red, false, 4.0f);
	//Capsule trace by channel   
	bool isHit = GetWorld()->SweepSingleByChannel(result, localStart, localEnd, FQuat::Identity, ECC_Visibility, myColisionShape, myColisionQP);
	if (isHit)
	{
		//Debug capsule trace by channel end 
		DrawDebugSphere(GetWorld(),result.Location, myColisionShape.GetSphereRadius(), 20, FColor::Red, false, 4.0f);
		localStart = muzzleWL;
		localEnd = muzzleWL + (UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(muzzleWL, result.ImpactPoint)) * 10000000.0f);
		//Debug line trace by channel   
		DrawDebugLine(GetWorld(), localStart, localEnd, FColor::Green, false, 4.0f);
		//Line trace bu chenal
		GetWorld()->LineTraceSingleByChannel(result, localStart, localEnd, ECC_Visibility, myColisionQP);
		//recording the hit point
		FVector hitLocation = result.Location;
		//find damage
		float localDamage = FMath::Max<float>((damage / 2.0f), (damage - ((UKismetMathLibrary::Vector_Distance(muzzleWL, hitLocation) / 1000.0f) * damageAlpha)));
		//recording the where hit
		FHitResult hitinfo;
		hitinfo.BoneName = result.BoneName;
		//Apply damage
		TSubclassOf<UDamageType> DamageType;
		UGameplayStatics::ApplyPointDamage(result.GetActor(), localDamage, muzzleWL, hitinfo, GetOwner()->GetInstigatorController(), ignore, DamageType);
		//if hit
		return true;
	}
	//if no hit
	return false;
}


