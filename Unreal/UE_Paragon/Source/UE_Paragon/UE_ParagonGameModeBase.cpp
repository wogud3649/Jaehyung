// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE_ParagonGameModeBase.h"
#include "GameFramework/Character.h"

AUE_ParagonGameModeBase::AUE_ParagonGameModeBase()
{
	static ConstructorHelpers::FClassFinder<ACharacter> myCharacter(TEXT("Blueprint'/Game/BluePrints/BP_MyCharacter.BP_MyCharacter_C'"));

	if (myCharacter.Succeeded())
		DefaultPawnClass = myCharacter.Class;
}