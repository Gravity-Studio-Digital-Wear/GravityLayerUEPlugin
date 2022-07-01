#pragma once
#include "CoreMinimal.h"
#include "Metadata.h"

class GRAVITYLAYER_API IWearableWithMetadata
{
public:
	virtual FString getTitle() = 0;
	virtual TArray<UGLMetadata*> getMetadata() = 0;
};