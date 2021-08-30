// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyWeaponProjectHUD.generated.h"

UCLASS()
class AMyWeaponProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyWeaponProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

