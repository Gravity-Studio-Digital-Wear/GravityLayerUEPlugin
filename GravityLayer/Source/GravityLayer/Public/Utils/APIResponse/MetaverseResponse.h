#pragma once

#include "CoreMinimal.h"
#include "MetaverseResponse.generated.h"



USTRUCT(Blueprintable)
struct FMetadataAttributes
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString value;
};

USTRUCT(Blueprintable)
struct FProductMetadata
{
    GENERATED_USTRUCT_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString metaverseId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString modelUrl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString previewImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray <FMetadataAttributes> attributes;
};


USTRUCT(Blueprintable)
struct FWardrobeData
{
    GENERATED_USTRUCT_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString _id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray <FString> images;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray <FProductMetadata> metadata;
};

  USTRUCT(Blueprintable)
    struct FWardrobeResult
    {
      GENERATED_USTRUCT_BODY()
    public:

          UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TArray<FWardrobeData> products;
    };








