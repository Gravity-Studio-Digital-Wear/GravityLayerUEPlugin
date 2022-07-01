#pragma once

#include "CoreMinimal.h"

#include "IFetchWearablesByAddress.generated.h"

class FGetNFTResponseDataAsyncDelegate;

UINTERFACE(MinimalAPI, Blueprintable)
class UFetchWearablesByAddress : public UInterface
{
	GENERATED_BODY()
};


class IFetchWearablesByAddress
{
	GENERATED_BODY()

public:

	virtual TArray<FString> GetNFTsByAddress(FString address) = 0;
	virtual FGetNFTResponseDataAsyncDelegate* GetOnNFTsByAddress() = 0;

};
