// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EntryPoints/MetaverseEntryPoint.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "GravityLayer.h"

/**
 * @brief Gravity Layer Module is the responsible for starting up plugin
 */
class GRAVITYLAYER_API FGravityLayerModule : public IModuleInterface
{
private:
	
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void PostLoadCallback() override;
	virtual void ShutdownModule() override;
};
