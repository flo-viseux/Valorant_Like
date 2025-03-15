// Copyright Epic Games, Inc. All Rights Reserved.

#include "Valorant_LikeGameMode.h"
#include "Valorant_LikeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AValorant_LikeGameMode::AValorant_LikeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
