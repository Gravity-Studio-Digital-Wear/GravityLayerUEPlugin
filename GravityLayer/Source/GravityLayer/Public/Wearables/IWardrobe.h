#pragma once
#include "CoreMinimal.h"
#include "Wearables\Wearable.h"
#include "IWardrobe.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStockUpdatedAsyncDelegate);

UINTERFACE(MinimalAPI, Blueprintable)
class UWardrobe : public UInterface
{
	GENERATED_BODY()
};


class IWardrobe
{
	GENERATED_BODY()

public:

	virtual TArray<UWearable*>* GetWearables() = 0;

};
