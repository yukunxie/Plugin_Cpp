// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Plugin_CppGameMode.h"
#include "Plugin_CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlugin_CppGameMode::APlugin_CppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
