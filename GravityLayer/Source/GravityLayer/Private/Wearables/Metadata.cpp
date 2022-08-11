#include "Wearables\Metadata.h"
#include "Utils\HTTPClient.h"
#include "ImageUtils.h"
#include "Modules\ModuleManager.h"
#include "Kismet\GameplayStatics.h"


UGLMetadata::UGLMetadata()
{
}

void UGLMetadata::SetMetadata(FString modelUrl, TMap<FString, FString> attributes)
{
	ModelUrl = modelUrl;
	Attributes = attributes;
}
FString UGLMetadata::GetModelUrl()
{
    return !ModelUrl.IsEmpty()? ModelUrl:"";
}

TMap<FString, FString>* UGLMetadata::GetAttributes()
{
    return &Attributes;
}

UTexture2D* UGLMetadata::GetPreviewImage()
{
    return PreviewImage;
}

void UGLMetadata::DownloadPreviewImage(FString url)
{
	OnImageDownloadedResponse.AddDynamic(this, &UGLMetadata::OnGetImageResponseReceived);
	UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
	httpClient->CallImageURL(url, OnImageDownloadedResponse);
}

void UGLMetadata::OnGetImageResponseReceived(UVaRestRequestJSON* restRequest)
{
	OnImageDownloadedResponse.RemoveDynamic(this, &UGLMetadata::OnGetImageResponseReceived);
	TArray<uint8> ImageData = restRequest->GetResponseContent();
	if(ImageData.Num()>0)
		PreviewImage = FImageUtils::ImportBufferAsTexture2D(ImageData);
}
