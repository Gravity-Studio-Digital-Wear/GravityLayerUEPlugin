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
    _metaverseAPIWrapper->OnGetNFTs.AddDynamic(this, &UStock::GetAllInteroperableWearables);
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
    FWardrobeResult wResult;
    FString code = "{\"products\":" + wearableData + "}";
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
    OnStockUpdated.Broadcast();
}

void UStock::FillStockFromJsonString(FString jsonString)
{
   
   
}
