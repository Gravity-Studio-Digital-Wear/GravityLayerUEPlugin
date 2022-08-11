#include "Wearables\Stock.h"
#include "Utils\MetaverseAPIWrapper.h"

#include "Json.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"

#include "Utils\APIResponse\MetaverseResponse.h"
#include "Wearables\WearableBase.h"


TArray<UWearable*>* UStock::GetWearables()
{
    return &Wearables;
}


UStock::UStock()
{
}

void UStock::SetMetaverse(UMetaverseAPIWrapper* wrapper)
{
    _metaverseAPIWrapper = wrapper;
    _metaverseAPIWrapper->OnGetNFTs.AddUniqueDynamic(this, &UStock::GetAllInteroperableWearables);
}

void UStock::Add(UWearable* const wearable)
{
    Wearables.Add(wearable);
}

void UStock::Remove(UWearable* const wearable)
{
    Wearables.Remove(wearable);
}

bool UStock::Contains(UWearable* const wearable)
{
    return Wearables.Contains(wearable);
}

int32_t UStock::lenght()
{
    return Wearables.Num();
}

UMetaverseAPIWrapper* UStock::GetMetaverse()
{
    return _metaverseAPIWrapper;
}

UStock::~UStock()
{
}

void UStock::FetchAllInteroperableWearables()
{
    _metaverseAPIWrapper->GetNFTs();
}

void UStock::GetAllInteroperableWearables(FString wearableData)
{
    GetWearables()->Empty();
    FString code = "{\"products\":" + wearableData + "}";
    FillStockFromJsonString(code);
    OnStockUpdated.Broadcast();
}

void UStock::FillStockFromJsonString(FString jsonString)
{
    FWardrobeResult wResult;
    if (FJsonObjectConverter::JsonObjectStringToUStruct(jsonString, &wResult, 0, 0))
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
}
