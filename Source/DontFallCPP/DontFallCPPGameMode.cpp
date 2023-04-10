// Copyright Epic Games, Inc. All Rights Reserved.

#include "DontFallCPPGameMode.h"
#include "DontFallCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADontFallCPPGameMode::ADontFallCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
