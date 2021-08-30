
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "LineTraceFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYWEAPONPROJECT_API ULineTraceFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULineTraceFireComponent();

	UFUNCTION(BlueprintCallable)
		bool Fire(FVector cameraWL, FVector cameraFW, FVector muzzleWL, AActor* ignore, float damage, float damageAlpha, float aimAsist);

};
