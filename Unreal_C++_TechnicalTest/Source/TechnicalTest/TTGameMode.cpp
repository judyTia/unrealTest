// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TTGameMode.h"
#include "TTHUD.h"
#include "TTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATTGameMode::ATTGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/TechnicalTest/Blueprints/TechnicalTestCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATTHud::StaticClass();
}

const FElementalDefinition& ATTGameMode::GetElementalDefinition(uint8 elementType)
{
	for (const FElementalDefinition& elementalDefinition : ElementalDefinitions)
	{
		if (elementalDefinition.ElementType == elementType)
		{
			return elementalDefinition;
		}
	}

	return ElementalDefinitions[0];
}
