// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyWeaponProjectGameMode.h"
#include "MyWeaponProjectHUD.h"
#include "MyWeaponProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyWeaponProjectGameMode::AMyWeaponProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMyWeaponProjectHUD::StaticClass();
}
