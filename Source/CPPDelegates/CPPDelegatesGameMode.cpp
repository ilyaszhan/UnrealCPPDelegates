// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPDelegatesGameMode.h"
#include "CPPDelegatesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPPDelegatesGameMode::ACPPDelegatesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
