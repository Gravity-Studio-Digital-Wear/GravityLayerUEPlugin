#pragma once
#include "CoreMinimal.h"
#include "Wearables\IStock.h"
#include "Wearables\IWardrobe.h"

#include "Stock.generated.h"


UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UStock : public UObject , public IStockInterface, public IWardrobe
{
	GENERATED_BODY()
private:

	
	UMetaverseAPIWrapper* _metaverseAPIWrapper;

	void FillStockFromJsonString(FString jsonString);
protected:

	UPROPERTY(BlueprintReadOnly)
	TArray<UWearable*> Wearables;

public:
	UStock();
	virtual ~UStock();

	void SetMetaverse(UMetaverseAPIWrapper* wrapper);
	
	
	TArray<UWearable*>* GetWearables();

	void FetchAllInteroperableWearables();

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void GetAllInteroperableWearables(FString wearableData);

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FOnStockUpdatedAsyncDelegate OnStockUpdated;
};