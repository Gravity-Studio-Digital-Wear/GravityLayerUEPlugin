#pragma once
#include "CoreMinimal.h"
#include "IStock.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UStockInterface : public UInterface
{
	GENERATED_BODY()
};




class IStockInterface
{
	GENERATED_BODY()
public:
	virtual  void FetchAllInteroperableWearables() = 0;
};