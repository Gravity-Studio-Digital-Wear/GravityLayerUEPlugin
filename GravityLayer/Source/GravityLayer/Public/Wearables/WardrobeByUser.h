#pragma once

#include "CoreMinimal.h"
#include"IWardrobe.h"

#include "WardrobeByUser.generated.h"


class IFetchWearablesByAddress;

UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UWardrobeByUser : public UObject, public IWardrobe 
{
	GENERATED_BODY()
public:
	UWardrobeByUser();
	void SetWardrobeByUser(IFetchWearablesByAddress* APIWrapper);
	virtual ~UWardrobeByUser();

	void FetchInteroperableWearables(FString address);
	TArray<UWearable*>* GetWearables();

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void FillWardrobeFromJsonString(FString jsonString);

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FOnStockUpdatedAsyncDelegate OnWardrobeUpdated;

protected:
	IFetchWearablesByAddress* _APIWrapper;
	TArray<UWearable*> Wearables;
	
	
};