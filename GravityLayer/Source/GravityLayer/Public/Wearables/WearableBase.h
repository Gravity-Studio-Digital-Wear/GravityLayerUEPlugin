#pragma once
#include "Engine/Texture2D.h"
#include "CoreMinimal.h"
#include "VaRestSubSystem.h"
#include "Wearable.h"
#include "WearableBase.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UWearableBase : public UWearable
{
	GENERATED_BODY()
private:
	FString Title;
	UTexture2D* PreviewImage;
	FString ModelUrl;
	FString MetaverseId;

public:
	UWearableBase();
	void SetWearableBase(FString title, FString modelUrl);
	virtual ~UWearableBase() ;

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	virtual FString GetTitle() override ;

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	virtual UTexture2D* GetPreviewImage() override;

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	virtual FString GetModelUrl() override;

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void DownloadPreviewImage(FString url);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void OnGetImageResponseReceived(UVaRestRequestJSON* restRequest);

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate OnImageDownloadedResponse;
};