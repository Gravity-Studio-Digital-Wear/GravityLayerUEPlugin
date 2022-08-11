#pragma once
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Utils/HTTPClient.h"
#include "Utils/APIResponse/MetaverseResponse.h"
#include "GravityLayerTests.generated.h"

static class MockDataCreator {
public :
	static FString CreateMockWardrobeResult();
	static UTexture2D* CreateMockPreviewImage();
	static TArray64<uint8> CreateMockPreviewImageData(uint8 TextureWidth = 100, uint8 TextureHeight = 128);
	static FString CreteMockNFTData();
	static FWardrobeData CreateMockWardrobeData();
};

UCLASS()
class UMockHTTPClient : public UEngineSubsystem
{
	GENERATED_BODY()

public :
	FString const GetNFTSLink = "https://gravity-dev.easychain.dev/api/nfts";
	FString const GetNFTsByAddressLink = "https://gravity-dev.easychain.dev/api/nfts/getByAddress?address=0x39b7d171e693b3e6270c40899e46c90016e3bd71";
	FString const GetModelMetadataByNftLink ="https://gravity-dev.easychain.dev/api/nfts/getModelByNft?contractId=0x2953399124f0cbb46d2cbacd8a89cf0599974963&tokenTypeId=75437324160650951662245703982020702172073797313123328702383515790577235918948";

public:
	UMockHTTPClient();
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:

	FString CallURL(const FString& URL, const FString& jwt, const FString& secret, FVaRestCallDelegate& Callback);
	TArray64<uint8> CallImageURL(const FString& URL, FVaRestCallDelegate& Callback);
	TMap<FString, FString> CreateHeaderParameters(const FString& jwt, const FString& secret);


	//void OnGetNFTsResponseReceived(UVaRestRequestJSON* restRequest);
};

#if WITH_DEV_AUTOMATION_TESTS

#endif //WITH_DEV_AUTOMATION_TESTS