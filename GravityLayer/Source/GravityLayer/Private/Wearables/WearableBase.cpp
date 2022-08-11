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

void UWearableBase::SetWearableBase(FString title, FString modelUrl, FString metaverseId)
{
	SetWearableBase(title, modelUrl);
	MetaverseId = metaverseId;
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

FString UWearableBase::GetMetaverseId()
{
	return MetaverseId;
}

FString UWearableBase::GetModelUrl()
{
	return ModelUrl;
}

void UWearableBase::SetPreviewImage(UTexture2D* image)
{
	PreviewImage = image;
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
	SetPreviewImage(FImageUtils::ImportBufferAsTexture2D(ImageData));
}
