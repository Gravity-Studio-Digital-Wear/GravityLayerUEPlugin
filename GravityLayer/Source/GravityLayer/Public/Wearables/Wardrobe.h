#pragma once
#include "IWardrobe.h"
#include "CoreMinimal.h"

class IFetchWearablesByAddress;



class GRAVITYLAYER_API Wardrobe : public IWardrobe
{
private:
	IFetchWearablesByAddress* _connection;
	TArray<UWearable*> Wearables;
	FString _metaverseId;

public:

	Wardrobe(IFetchWearablesByAddress* connection, FString metaverseId);
	virtual ~Wardrobe();

	TArray<UWearable*>* GetWearables();
	void FetchInteroperableWearables();
	void FillWardrobeFromJsonString(FString jsonString);

};
