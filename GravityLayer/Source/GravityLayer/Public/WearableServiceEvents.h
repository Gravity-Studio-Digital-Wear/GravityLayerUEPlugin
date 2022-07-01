#pragma once
#include "CoreMinimal.h"
#include "Wearables/Metadata.h"
#include "Wearables/Wearable.h"
#include "VarestSubSystem.h"
#include "WearableServiceEvents.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FWearableServiceResponseAsyncDelegate, TArray<UGLMetadata*>, Asset);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWearableServicesUpdatedAsyncDelegate, TArray<UGLMetadata*>, WearableMetadata);


USTRUCT()
struct FWearableServiceResponse
{
	GENERATED_BODY()

	UPROPERTY()
	UWearable* wearable;

	UPROPERTY()
	FWearableServiceResponseAsyncDelegate Callback;
};


