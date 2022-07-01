// Copyright Epic Games, Inc. All Rights Reserved.


#include "GravityLayerSampleGameMode.h"
#include "GravityLayer.h"

AGravityLayerSampleGameMode::AGravityLayerSampleGameMode()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	if (GEngine) 
	{
		UGravityLayer* GLayer = GEngine->GetEngineSubsystem<UGravityLayer>();
		if (GLayer) 
		{
			GLayer->Configure();
			GLayer->ConsoleTest();
		}	
	}
	

}
