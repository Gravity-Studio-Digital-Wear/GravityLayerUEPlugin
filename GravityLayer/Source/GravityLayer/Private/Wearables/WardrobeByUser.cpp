#include "Wearables\WardrobeByUser.h"
#include "Utils\MetaverseAPIWrapper.h"
#include "Utils\IFetchWearablesByAddress.h"

#include "Json.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"

#include "Utils\APIResponse\MetaverseResponse.h"
#include "Wearables\WearableBase.h"

void UWardrobeByUser::SetWardrobeByUser(IFetchWearablesByAddress* APIWrapper)
{
	_APIWrapper = APIWrapper;
	_APIWrapper->GetOnNFTsByAddress()->AddDynamic(this, &UWardrobeByUser::FillWardrobeFromJsonString);
}

UWardrobeByUser::UWardrobeByUser()
{
}

UWardrobeByUser::~UWardrobeByUser()
{
}

void UWardrobeByUser::FetchInteroperableWearables(FString address)
{
	_APIWrapper->GetNFTsByAddress(address);
	
}

void UWardrobeByUser::FillWardrobeFromJsonString(FString jsonString)
{
	//UE_LOG(LogTemp, Warning, TEXT("UWardrobeByUser::FillWardrobeFromJsonString: %s"), *jsonString);
	Wearables.Empty();

	FWardrobeResult wResult;
	FString code = "{\"products\":" + jsonString + "}";
	if (FJsonObjectConverter::JsonObjectStringToUStruct(code, &wResult, 0, 0))
	{
		FWardrobeData* Wdata = nullptr;
		for (int i = 0; i < wResult.products.Num(); ++i)
		{
			Wdata = &wResult.products[i];
			if (Wdata->metadata.Num() > 0)
			{
				UWearableBase* m = NewObject<UWearableBase>();
				m->SetWearableBase(Wdata->name, Wdata->metadata[0].modelUrl);
				m->DownloadPreviewImage(Wdata->metadata[0].previewImage);
				GetWearables()->Add(m);
			}
		}
	}
	OnWardrobeUpdated.Broadcast();
}

TArray<UWearable*>* UWardrobeByUser::GetWearables()
{
	return &Wearables;
}
