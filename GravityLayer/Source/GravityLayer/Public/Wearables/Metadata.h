#pragma once
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"

#include "VaRestSubSystem.h"

#include "Metadata.generated.h"

//DECLARE_DYNAMIC_DELEGATE_OneParam(FGLRestCallImageDelegate, UVaRestRequestJSON*, Request);

UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UGLMetadata : public UObject
{
	GENERATED_BODY()
private:
	UTexture2D* PreviewImage;
	FString ModelUrl;
	TMap<FString, FString> Attributes;

public:
	UGLMetadata();

	void SetMetadata(FString modelUrl, TMap<FString, FString> attributes);

	FString GetModelUrl();
	TMap<FString, FString>* GetAttributes();
	UTexture2D* GetPreviewImage();

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void DownloadPreviewImage(FString url);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void OnGetImageResponseReceived(UVaRestRequestJSON* restRequest);

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate OnImageDownloadedResponse;
};
