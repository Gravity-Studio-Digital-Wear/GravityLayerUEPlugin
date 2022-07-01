#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Wearable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UWearableInferface : public UInterface
{
	GENERATED_BODY()
};


class IWearableInferface
{
	 GENERATED_BODY()

public:

	virtual FString GetTitle()=0;
	virtual UTexture2D* GetPreviewImage() = 0;
	virtual FString GetModelUrl() = 0;
	virtual void GetModelData(FString ModelData) = 0;
};

UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UWearable : public UObject, public IWearableInferface 
{
	GENERATED_BODY()
public:
	
	virtual FString GetTitle() override;
	
	virtual UTexture2D* GetPreviewImage() override;

	virtual FString GetModelUrl() override;

	virtual void GetModelData(FString ModelData) override;
};
