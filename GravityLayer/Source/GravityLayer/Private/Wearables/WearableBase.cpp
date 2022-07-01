#include "Wearables\WearableBase.h"

#include "Utils\HTTPClient.h"

#include "Json.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "ImageUtils.h"

void UWearableBase::SetWearableBase(FString title, FString modelUrl)
{
	Title = title;
	ModelUrl = modelUrl;
}

UWearableBase::UWearableBase()
{

}

UWearableBase::~UWearableBase()
{
}

FString UWearableBase::GetTitle()
{
	return Title;
}

UTexture2D* UWearableBase::GetPreviewImage()
{
	return PreviewImage;
}

FString UWearableBase::GetModelUrl()
{
	return ModelUrl;
}

void UWearableBase::DownloadPreviewImage(FString url)
{
	OnImageDownloadedResponse.AddDynamic(this, &UWearableBase::OnGetImageResponseReceived);
	UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
	httpClient->CallImageURL(url, OnImageDownloadedResponse);
}

void UWearableBase::OnGetImageResponseReceived(UVaRestRequestJSON* restRequest)
{
	OnImageDownloadedResponse.RemoveDynamic(this, &UWearableBase::OnGetImageResponseReceived);
	TArray<uint8> ImageData = restRequest->GetResponseContent();
	PreviewImage = FImageUtils::ImportBufferAsTexture2D(ImageData);
}
