#include "Wearables/WearableServices.h"
#include "Utils/MetaverseAPIWrapper.h"

#include "Json.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"

#include "Utils\APIResponse\MetaverseResponse.h"
#include "Wearables\WearableBase.h"
#include "Wearables\Metadata.h"

void UWearableServices::SetWearableServices(UMetaverseAPIWrapper* wrapper)
{
	_metaverseAPIWrapper = wrapper;
	_metaverseAPIWrapper->OnGetModelMetadataByNft.AddUniqueDynamic(this, &UWearableServices::GetAllInteroperableWearables);
}

UMetaverseAPIWrapper* UWearableServices::GetMetaverse()
{
    return _metaverseAPIWrapper;
}

UWearableServices::UWearableServices()
{
}

void UWearableServices::GetWearableMetadata(FString contractId, FString tokenId, FString filter)
{
	_metaverseAPIWrapper->GetModelMetadataByNft(contractId, tokenId, filter);
}

void UWearableServices::GetWearableMetadata(FString contractId, FString tokenId, FString filter, FVaRestCallDelegate& Callback)
{
    _metaverseAPIWrapper->GetModelMetadataByNftWithCallBack(contractId, tokenId, filter, Callback);
}

void UWearableServices::GetAllInteroperableWearables(FString wearableData)
{
    TArray<UGLMetadata*> wearableMetadata = GetAllInteroperableWearablesFromData(wearableData);
    OnWearableMetadataUpdate.Broadcast(wearableMetadata);
}

TArray<UGLMetadata*> UWearableServices::GetAllInteroperableWearablesFromData(FString wearableData)
{
    FString code = "{\"metadata\":" + wearableData + "}";
    FWardrobeData wResult;
    TArray<UGLMetadata*> wearableMetadata;
    if (FJsonObjectConverter::JsonObjectStringToUStruct(code, &wResult, 0, 0))
    {
        if (wResult.metadata.Num() == 0) return wearableMetadata;
        FProductMetadata* Wdata = nullptr;
        for (int i = 0; i < wResult.metadata.Num(); ++i)
        {
            Wdata = &wResult.metadata[i];

            TMap<FString, FString> attributes;

            for (int j = 0; j < Wdata->attributes.Num(); j++)
            {
                attributes.Add(Wdata->attributes[j].name, Wdata->attributes[j].value);
            }

            UGLMetadata* m = NewObject<UGLMetadata>();
            m->SetMetadata(Wdata->modelUrl, attributes);
            m->DownloadPreviewImage(Wdata->previewImage);
            wearableMetadata.Add(m);
        }
    }
    return wearableMetadata;
}
