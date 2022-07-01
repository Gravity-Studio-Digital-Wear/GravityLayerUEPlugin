#include "Utils\MetaverseAPIWrapper.h"

#include <GravityLayer/Public/Utils/HTTPClient.h>
#include "Delegates/DelegateSignatureImpl.inl"
#include "Utils/HTTPClient.h"

FString UMetaverseAPIWrapper::GetNFTs()
{
    FString url = _apiUrl + "/nfts";
    if (GEngine)
    {
        UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
        httpClient->CallURL(url, "", _secret, GetNTFSRestCallback);
    }
    return FString();
}

TArray<FString> UMetaverseAPIWrapper::GetNFTsByAddress(FString address)
{
    FString url = _apiUrl + "/nfts/getByAddress?address=" + address;
    if (GEngine) 
    {
        UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
        httpClient->CallURL(url, "", _secret, GetNFTsByAddressCallback);
    }
    return TArray<FString>();
}

void UMetaverseAPIWrapper::GetModelMetadataByNft(FString contractId, FString tokenId, FString filter)
{
    FString  url = _apiUrl + "/nfts/getModelByNft?contractId=" + contractId + "&tokenTypeId=" + tokenId;

    if (filter.Len() > 0)
    {
        url += "&" + filter;
    }

    if (GEngine)
    {
        UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
        httpClient->CallURL(url, "", _secret, GetModelMetadataByNftCallBack);
    }
}

void UMetaverseAPIWrapper::GetModelMetadataByNftWithCallBack(FString contractId, FString tokenId, FString filter, FVaRestCallDelegate& Callback)
{
    FString  url = _apiUrl + "/nfts/getModelByNft?contractId=" + contractId + "&tokenTypeId=" + tokenId;

    if (filter.Len() > 0)
    {
        url += "&" + filter;
    }

    if (GEngine)
    {
        UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
        httpClient->CallURL(url, "", _secret, Callback);
    }
}

void UMetaverseAPIWrapper::OnGetNFTsResponseReceived(UVaRestRequestJSON* restRequest)
{
    OnGetNFTs.Broadcast(restRequest->GetResponseContentAsString());
}

void UMetaverseAPIWrapper::OnGetNFTsByAddressResponseReceived(UVaRestRequestJSON* restRequest)
{   
    OnNFTsByAddress.Broadcast(restRequest->GetResponseContentAsString());
}

void UMetaverseAPIWrapper::OnGetModelMetadataByNftResponseReceived(UVaRestRequestJSON* restRequest)
{
    OnGetModelMetadataByNft.Broadcast(restRequest->GetResponseContentAsString());
}

void UMetaverseAPIWrapper::HTTPRequestResponse(UVaRestRequestJSON* restRequest)
{
    
}

FGetNFTResponseDataAsyncDelegate* UMetaverseAPIWrapper::GetOnNFTsByAddress()
{
    return 	&OnNFTsByAddress;
}

UMetaverseAPIWrapper::UMetaverseAPIWrapper()
{
   
}

UMetaverseAPIWrapper::UMetaverseAPIWrapper(FString apiUrl, FString secret)
{
    InitializeAPIWrapper(apiUrl, secret);
}

UMetaverseAPIWrapper::~UMetaverseAPIWrapper()
{
}

void UMetaverseAPIWrapper::InitializeAPIWrapper(const FString& apiUrl, const FString& secret)
{
    _apiUrl = apiUrl;
    _secret = secret;
    GetNTFSRestCallback.AddDynamic(this, &UMetaverseAPIWrapper::OnGetNFTsResponseReceived);
    GetNFTsByAddressCallback.AddDynamic(this, &UMetaverseAPIWrapper::OnGetNFTsByAddressResponseReceived);
    GetModelMetadataByNftCallBack.AddDynamic(this, &UMetaverseAPIWrapper::OnGetModelMetadataByNftResponseReceived);;
}
