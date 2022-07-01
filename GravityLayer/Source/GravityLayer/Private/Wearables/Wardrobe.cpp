#include "Wearables\Wardrobe.h"

TArray<UWearable*>* Wardrobe::GetWearables()
{
    return &Wearables;
}

Wardrobe::Wardrobe(IFetchWearablesByAddress* connection, FString metaverseId)
{
    _metaverseId = metaverseId;
    _connection = connection;
}

void Wardrobe::FetchInteroperableWearables()
{
}

void Wardrobe::FillWardrobeFromJsonString(FString jsonString)
{

}

Wardrobe::~Wardrobe()
{
}
