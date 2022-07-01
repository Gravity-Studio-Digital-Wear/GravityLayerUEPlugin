#include "Wearables\WearableWithMetadata.h"

FString WearableWithMetadata::getTitle()
{
    return Title;
}

TArray<UGLMetadata*> WearableWithMetadata::getMetadata()
{
    return Metadata;
}
