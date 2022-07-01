#pragma once

#include "CoreMinimal.h"
#include "Wearables\Metadata.h"
#include "WearableServiceEvents.h"
#include "WearableServices.generated.h"

class UMetaverseAPIWrapper;

UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UWearableServices : public UObject
{
	GENERATED_BODY()
private:
	UMetaverseAPIWrapper* _metaverseAPIWrapper;

public:
	UWearableServices();

	void SetWearableServices(UMetaverseAPIWrapper* wrapper);

	void GetWearableMetadata(FString contractId, FString tokenId, FString filter = "");

	void GetWearableMetadata(FString contractId, FString tokenId, FString filter, FVaRestCallDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void GetAllInteroperableWearables(FString wearableData);

	TArray<UGLMetadata*> GetAllInteroperableWearablesFromData(FString wearableData);

	FWearableServicesUpdatedAsyncDelegate OnWearableMetadataUpdate;
};