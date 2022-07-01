#pragma once

#include "CoreMinimal.h"
#include "VaRestSubsystem.h"
#include "IFetchWearablesByAddress.h"
#include <Http.h>
#include "MetaverseAPIWrapper.generated.h"

//DECLARE_DYNAMIC_DELEGATE_ThreeParams(FGLRestCallDelegate, FHttpRequestPtr, FHttpResponsePtr, bool);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetNFTResponseDataArrayAsyncDelegate, TArray<FString>, ResponseJsonData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetNFTResponseDataAsyncDelegate, FString, ResponseJsonData);

UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UMetaverseAPIWrapper : public UObject, public IFetchWearablesByAddress
{
	GENERATED_BODY()

protected:
	FString _apiUrl;
	FString _secret;
public:

	UMetaverseAPIWrapper();
	UMetaverseAPIWrapper(FString apiUrl, FString secret);
	virtual ~UMetaverseAPIWrapper();

	void InitializeAPIWrapper(const FString& apiUrl, const FString& secret);

	UFUNCTION(BlueprintCallable)
	FString GetNFTs();
	
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetNFTsByAddress(FString address);

	UFUNCTION(BlueprintCallable)
	void GetModelMetadataByNft(FString contractId, FString tokenId, FString filter = "");

	//UFUNCTION(BlueprintCallable)
	void GetModelMetadataByNftWithCallBack(FString contractId, FString tokenId, FString filter, FVaRestCallDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void OnGetNFTsResponseReceived(UVaRestRequestJSON* restRequest);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void OnGetNFTsByAddressResponseReceived(UVaRestRequestJSON* restRequest);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void OnGetModelMetadataByNftResponseReceived(UVaRestRequestJSON* restRequest);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void HTTPRequestResponse(UVaRestRequestJSON* restRequest);

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate GetNTFSRestCallback;

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate GetNFTsByAddressCallback;

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate GetModelMetadataByNftCallBack;

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FGetNFTResponseDataAsyncDelegate OnGetNFTs;

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FGetNFTResponseDataAsyncDelegate OnNFTsByAddress;

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FGetNFTResponseDataAsyncDelegate OnGetModelMetadataByNft;

	FGetNFTResponseDataAsyncDelegate* GetOnNFTsByAddress();

};