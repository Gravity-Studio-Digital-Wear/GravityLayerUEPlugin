#include "GravityLayerTests.h"

#include "Tests/AutomationEditorCommon.h"

#include <GravityLayerModule.h>
#include "Utils/MetaverseAPIWrapper.h"
#include "EntryPoints/MetaverseEntryPoint.h"
#include "Wearables/Stock.h"
#include "Wearables/WardrobeByUser.h"
#include "Wearables/WearableServices.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/ObjectLibrary.h"
#include "UObject/SoftObjectPath.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Wearables/WearableBase.h"
#include "ImageUtils.h"
#include "Engine/Texture.h"

#include "glTFRuntimeFunctionLibrary.h"
#include <JsonUtilities.h>
#include <Json.h>

#include "Utils/HTTPClient.h"
#include "Utils/APIResponse/MetaverseResponse.h"

#include "ImageUtils.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"

#include "Wearables/Metadata.h"

#if WITH_DEV_AUTOMATION_TESTS

// Start up tests
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerConfigureTest, "GravityLayer.Configure.GLSubSystem", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerConfigureMetaverseEntryPointTest, "GravityLayer.Configure.MetaverseEntryPoint", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerConfigureStockTest, "GravityLayer.Configure.Stock", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerConfigureWardrobeTest, "GravityLayer.Configure.Wardrobe", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerEmptyTest, "GravityLayer.EmptyContainers", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Stock add remove item
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerStockCollectableOperations, "GravityLayer.Stock.Containers", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerStockCreateFromJson, "GravityLayer.Stock.CreateFromJson", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Wardrobe add remove item
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerWardrobeCollectableOperations, "GravityLayer.Wardrobe.Containers", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerWardrobeCreateFromJson, "GravityLayer.Wardrobe.CreateFromJson", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Werable Create Empty
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerWearableCreateEmpty, "GravityLayer.Wearable", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerWearableDownloadPreviewImage, "GravityLayer.Wearable.CreatePreviewImageFromJson", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Skeletal mesh creation test
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerSkeletalMeshAddTest, "GravityLayer.SkeletalMesh.AddSkeletalMesh", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerSkeletalMeshSetupTest, "GravityLayer.SkeletalMesh.SetupSkeletonCharacter", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// GLTF GLB Create Model from text
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerGLBTOSkeletalMesh, "GravityLayer.GLTF.GLBTOSkeletalMesh", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// Wearable Services
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerWearableServicesParseWearableData, "GravityLayer.WearableServices.CreateFromJson", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

// HTTP Client Tests
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGravityLayerHTTPHeaderTest, "GravityLayer.HTTP.HTTPHeader", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)


// Your function must be named RunTest
bool FGravityLayerConfigureTest::RunTest(const FString& Parameters)
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	TestTrue("GLSubSystem is created correctly", GLSubSystem != nullptr);
	if (GLSubSystem)
	{
		const FString account = "0x39b7d171e693b3e6270c40899e46c90016e3bd71";
		const FString apiurl = "https://gravity-dev.easychain.dev/api";
		const FString secret = "ZrikRzDrFS9jyVX5UBoVLOdD";

		GLSubSystem->ConfigureWithParams(account, apiurl, secret);
			
		TestEqual("GL Subsystem Accout Id: ", GLSubSystem->GetAccountId(), account);
		TestEqual("GL Subsystem API Url: ", GLSubSystem->GetApiUrl(), apiurl);
		TestEqual("GL Subsystem Secret: ", GLSubSystem->GetSecret(), secret);

		GLSubSystem->Deinitialize();
	}
	else
		return false;
	// We can return False to fail the error, but  
	return true;
}

bool FGravityLayerConfigureMetaverseEntryPointTest::RunTest(const FString& Parameters)
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	TestTrue("GLSubSystem is created correctly", GLSubSystem != nullptr);
	if (GLSubSystem)
	{
		const FString account = "0x39b7d171e693b3e6270c40899e46c90016e3bd71";
		const FString apiurl = "https://gravity-dev.easychain.dev/api";
		const FString secret = "ZrikRzDrFS9jyVX5UBoVLOdD";

		GLSubSystem->ConfigureWithParams(account, apiurl, secret);

		TestEqual("Metaverse Entry Point API URL: ", GLSubSystem->GetMetaverseEntryPoint()->GetGLMetaverseAPIWrapper()->GetApiUrl(), apiurl);
		TestEqual("Metaverse Entry Point Secret: ", GLSubSystem->GetMetaverseEntryPoint()->GetGLMetaverseAPIWrapper()->GetSecret(), secret);
		GLSubSystem->Deinitialize();
	}
	else
		return false;
	// We can return False to fail the error, but  
	return true;
}

bool FGravityLayerConfigureStockTest::RunTest(const FString& Parameters)
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	TestTrue("GLSubSystem is created correctly", GLSubSystem != nullptr);
	if (GLSubSystem)
	{
		const FString account = "0x39b7d171e693b3e6270c40899e46c90016e3bd71";
		const FString apiurl = "https://gravity-dev.easychain.dev/api";
		const FString secret = "ZrikRzDrFS9jyVX5UBoVLOdD";

		GLSubSystem->ConfigureWithParams(account, apiurl, secret);

		TestEqual("Stock Metaverse Entry Point: ", GLSubSystem->GetMetaverseEntryPoint()->GetStock()->GetMetaverse() == GLSubSystem->GetMetaverseEntryPoint()->GetGLMetaverseAPIWrapper(), true);
		TestEqual("Stock API URL: ", GLSubSystem->GetMetaverseEntryPoint()->GetStock()->GetMetaverse()->GetApiUrl(), apiurl);
		TestEqual("Stock API URL: ", GLSubSystem->GetMetaverseEntryPoint()->GetStock()->GetMetaverse()->GetSecret(), secret);
		GLSubSystem->Deinitialize();
	}
	else
		return false;

	// We can return False to fail the error, but  
	return true;
}

bool FGravityLayerConfigureWardrobeTest::RunTest(const FString& Parameters)
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	TestTrue("GLSubSystem is created correctly", GLSubSystem != nullptr);
	if (GLSubSystem)
	{
		const FString account = "0x39b7d171e693b3e6270c40899e46c90016e3bd71";
		const FString apiurl = "https://gravity-dev.easychain.dev/api";
		const FString secret = "ZrikRzDrFS9jyVX5UBoVLOdD";

		GLSubSystem->ConfigureWithParams(account, apiurl, secret);

		TestEqual("Wardrobe Services Metaverse Entry Point: ", GLSubSystem->GetMetaverseEntryPoint()->GetWardrobeServices()->GetMetaverse() == GLSubSystem->GetMetaverseEntryPoint()->GetGLMetaverseAPIWrapper(), true);
		TestEqual("Wardrobe Services API URL: ", GLSubSystem->GetMetaverseEntryPoint()->GetWardrobeServices()->GetMetaverse()->GetApiUrl(), apiurl);
		TestEqual("Wardrobe Services API URL: ", GLSubSystem->GetMetaverseEntryPoint()->GetWardrobeServices()->GetMetaverse()->GetSecret(), secret);
		GLSubSystem->Deinitialize();
	}
	else
		return false;

	return true;
}

bool FGravityLayerEmptyTest::RunTest(const FString& Parameters) 
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	if (GLSubSystem) 
	{
		const FString account = "0x39b7d171e693b3e6270c40899e46c90016e3bd71";
		const FString apiurl = "https://gravity-dev.easychain.dev/api";
		const FString secret = "ZrikRzDrFS9jyVX5UBoVLOdD";

		GLSubSystem->ConfigureWithParams(account, apiurl, secret);
		TestEqual("Empty NFT Stock: ", GLSubSystem->GetMetaverseEntryPoint()->GetStock()->GetWearables()->Num(), 0);
		TestEqual("Empty NFT Wardrobe: ", GLSubSystem->GetMetaverseEntryPoint()->GetWardrobe()->GetWearables()->Num(), 0);
		GLSubSystem->Deinitialize();
	}
	else 
	{
		return false;
	}

	return true;

}

bool FGravityLayerSkeletalMeshAddTest::RunTest(const FString& Parameters)
{
	if (UWorld* GameWorld = GEditor->GetEditorWorldContext().World())
	{
		AActor* actor = GameWorld->SpawnActor<AActor>();
		UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
		// Check actor component is empty 
		USkeletalMeshComponent* empty = Cast<USkeletalMeshComponent>(actor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		// Add skeletal mesh component
		USkeletalMeshComponent* added = GLSubSystem->AddSkeletalMeshComponent(actor);

		TestEqual("should be without skeletal mesh : ", empty == NULL, true);
			
		USkeletalMeshComponent* searched = Cast<USkeletalMeshComponent>(actor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

		TestEqual("should be capable of adding Actor with skeletal mesh : ", added != NULL && added == searched, true);

		actor->Destroy();
	}
	else
		return false;
		
	
	return true;
}

bool FGravityLayerSkeletalMeshSetupTest::RunTest(const FString& Parameters)
{
	// get world context
	if (UWorld* GameWorld = GEditor->GetEditorWorldContext().World())
	{
		// Create empty actor 
		AActor* actor = GameWorld->SpawnActor<AActor>();
		UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	
		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		TSoftObjectPtr<USkeletalMesh> skeletalmeshLoader = TSoftObjectPtr<USkeletalMesh>(FSoftObjectPath(TEXT("SkeletalMesh'/GravityLayer/Character/TestCharacter/RPMFBX/SomniumPCVR_RPM_texresized_v4.SomniumPCVR_RPM_texresized_v4'")));
		const FSoftObjectPath& AssetRef = skeletalmeshLoader.ToSoftObjectPath();

		// load asset
		USkeletalMesh* mesh  = Cast<USkeletalMesh>(StreamableManager.LoadSynchronous(AssetRef));
		
		// add skeletal mesh componetn and assign mesh to it 
		USkeletalMeshComponent* added = GLSubSystem->SetupSkeletalMeshComponent(actor, mesh);

		TestEqual("should be capable of adding Skeletal Mesh: ", added != NULL && added->SkeletalMesh != NULL && added->SkeletalMesh == mesh, true);
		actor->Destroy();
		GLSubSystem->Deinitialize();
	}
	else
			return false;
		
	return true;
}

bool FGravityLayerStockCollectableOperations::RunTest(const FString& Parameters)
{
	UWorld* GameWorld = GEditor->GetEditorWorldContext().World();
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	if ( GameWorld && GLSubSystem)
	{
		GLSubSystem->Configure();
		UStock* stock = GLSubSystem->GetMetaverseEntryPoint()->GetStock();
		const FString title = "Test";
		const FString url = "TestURL";
		const FString id = "TestID";
		UWearableBase* m = NewObject<UWearableBase>();
		m->SetWearableBase(title, url, id);

		TestEqual("should be empty", stock->lenght(), 0);
		TestEqual("should not find cloth", stock->Contains(m), false);

		stock->Add(m);
		TestEqual("should be 1", stock->lenght(), 1);
		stock->Contains(m);
		TestEqual("should find cloth", stock->Contains(m), true);

		stock->Remove(m);
		TestEqual("should be 0", stock->lenght(), 0);
		TestEqual("should not find cloth after delete", stock->Contains(m), false);
		GLSubSystem->Deinitialize();
	}
	else
	{
		TestTrue("should be created correctly GameWorld ", GameWorld != nullptr);
		TestTrue("should be created correctly GLSubSystem ", GLSubSystem != nullptr);
		return false;
	}
		
	return true;
}

bool FGravityLayerWardrobeCollectableOperations::RunTest(const FString& Parameters)
{
	UWorld* GameWorld = GEditor->GetEditorWorldContext().World();
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	if (GameWorld && GLSubSystem)
	{
		GLSubSystem->Configure();
		UWardrobeByUser* wardrobe = GLSubSystem->GetMetaverseEntryPoint()->GetWardrobe();
		const FString title = "Test";
		const FString url = "TestURL";
		const FString id = "TestID";
		UWearableBase* m = NewObject<UWearableBase>();
		m->SetWearableBase(title, url, id);

		TestEqual("should be empty", wardrobe->lenght(), 0);
		TestEqual("should not find cloth", wardrobe->Contains(m), false);
		wardrobe->Add(m);
		TestEqual("should be 1", wardrobe->lenght(), 1);
		wardrobe->Contains(m);
		TestEqual("should find cloth", wardrobe->Contains(m), true);
		wardrobe->Remove(m);
		TestEqual("should be 0", wardrobe->lenght(), 0);
		TestEqual("should not find cloth after delete", wardrobe->Contains(m), false);
		GLSubSystem->Deinitialize();
	}
	else
	{
		TestTrue("should be created correctly GameWorld ", GameWorld != nullptr);
		TestTrue("should be created correctly GLSubSystem ", GLSubSystem != nullptr);
		return false;
	}
	return true;
}

bool FGravityLayerWearableCreateEmpty::RunTest(const FString& Parameters)
{
	const FString title = "Test";
	const FString url = "TestURL";
	const FString id = "TestID";
	UWearableBase* m = NewObject<UWearableBase>();
	TestEqual("should have empty Title : ", m->GetTitle().IsEmpty(), true);
	TestEqual("should have empty ModelUrl : ", m->GetModelUrl().IsEmpty(), true);
	TestEqual("should have empty MetaverseId : ", m->GetMetaverseId().IsEmpty(), true);
	TestEqual("should have empty PreviewImage : ", m->GetPreviewImage()== NULL, true);

	m->SetWearableBase(title, url, id);

	uint8 TextureWidth = 100;
	uint8 TextureHeight = 128;
	UTexture2D* RuntimeTexture = MockDataCreator::CreateMockPreviewImage();

	m->SetPreviewImage(RuntimeTexture);
	TestEqual("should have Title : ", m->GetTitle().Equals(title), true);
	TestEqual("should have : ", m->GetModelUrl().Equals(url), true);
	TestEqual("should have MetaverseId : ", m->GetMetaverseId().Equals(id), true);
	TestEqual("should have same texture with : ", m->GetPreviewImage()->GetSizeX() == TextureWidth , true);
	TestEqual("should have same texture height : ", m->GetPreviewImage()->GetSizeY() == TextureHeight, true);

	return true;
}

bool FGravityLayerWearableDownloadPreviewImage::RunTest(const FString& Parameters)
{
	UMockHTTPClient* httpClient = GEngine->GetEngineSubsystem<UMockHTTPClient>();
	if (httpClient)
	{
		uint8 TextureWidth = 100;
		uint8 TextureHeight = 128;
		UWearableBase* m = NewObject<UWearableBase>();
		FString code;
		TArray64<uint8> data;
		auto img = MockDataCreator::CreateMockPreviewImageData(TextureWidth, TextureHeight);

		m->SetPreviewImage(FImageUtils::ImportBufferAsTexture2D(img));
		TestEqual("should have same texture with : ", m->GetPreviewImage()->GetSizeX() == TextureWidth, true);
		TestEqual("should have same texture height : ", m->GetPreviewImage()->GetSizeY() == TextureHeight, true);
	}
	else 
	{
		TestTrue("should be created correctly httpClient ", httpClient != nullptr);
	}
	return true;
}

bool FGravityLayerGLBTOSkeletalMesh::RunTest(const FString& Parameters) 
{
	UWorld* GameWorld = GEditor->GetEditorWorldContext().World();
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	
	if (GLSubSystem && GameWorld)
	{
		FString LoadFromFileRelativePath = "Plugins/GravityLayer/Content/Character/GLB/SomniumPCVR_RPM_texresized.glb";
		
		AActor* actor = GameWorld->SpawnActor<AActor>();

		// LoadSkeleton for character
		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		TSoftObjectPtr<USkeleton> skeletalmeshLoader = TSoftObjectPtr<USkeleton>(FSoftObjectPath(TEXT("Skeleton'/GravityLayer/Character/RPM/Character/Fullbody/Mesh/SK_Mixamo_Skeleton.SK_Mixamo_Skeleton'")));
		const FSoftObjectPath& AssetRef = skeletalmeshLoader.ToSoftObjectPath();
		USkeleton* skeleton = Cast<USkeleton>(StreamableManager.LoadSynchronous(AssetRef));
		TestEqual("should have a skeleton.", skeleton != NULL, true);

		// Load GLB File
		FString TruePath = FPaths::Combine(FPaths::ProjectDir(), LoadFromFileRelativePath);
		UglTFRuntimeAsset* Asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(TruePath,
			false,
			GLSubSystem->GetglTFRuntimeConfig());

		TestEqual("should have a gltf runtime asset.", Asset != NULL, true);
		FString rootBone = "Armature";
		FJsonSerializableArray excludeNodes;

		// Load Skeletal Mesh 
		USkeletalMesh* skeletalMesh = Asset->LoadSkeletalMeshRecursive(rootBone, excludeNodes, GLSubSystem->GetglTFRuntimeSkeletalMeshConfig(rootBone, skeleton));
		TestEqual("should have a Skeletal Mesh: ", skeletalMesh != NULL, true);
		// Add Skeletal Mesh 
		USkeletalMeshComponent* added = GLSubSystem->SetupSkeletalMeshComponent(actor, skeletalMesh);
		TestEqual("should have a keletalMeshComponent.", skeletalMesh != NULL, true);

		actor->Destroy();
		GLSubSystem->Deinitialize();
	}
	else 
	{
		TestTrue("should be created correctly GameWorld ", GameWorld != nullptr);
		TestTrue("should be created correctly GLSubSystem ", GLSubSystem != nullptr);
		return false;
	}

	return true;
}

bool FGravityLayerHTTPHeaderTest::RunTest(const FString& Parameters)
{
	UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();

	TestTrue("should be a http client", httpClient != nullptr);
	if (httpClient)
	{
		TMap<FString,FString> header = httpClient->CreateHeaderParameters("jwt", "secret");
		TestEqual("should have a Authorization value", header["Authorization"], "Bearer jwt");
		TestEqual("should have a Authorization value", header["api-key"], "secret");
	}
	else
		return false;
	// We can return False to fail the error, but  
	return true;
}

bool FGravityLayerStockCreateFromJson::RunTest(const FString& Parameters)
{
	UMockHTTPClient* httpClient = GEngine->GetEngineSubsystem<UMockHTTPClient>();
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();

	if (httpClient && GLSubSystem)
	{
		
		UMetaverseAPIWrapper* gLMetaverseAPIWrapper = NewObject<UMetaverseAPIWrapper>();
		gLMetaverseAPIWrapper->InitializeAPIWrapper("apiUrl", "secret");
		UStock* stock = NewObject<UStock>();
		stock->SetMetaverse(gLMetaverseAPIWrapper);
		TestEqual("should have a 0 wearable in stock ", stock->GetWearables()->Num(), 0);;
		FString stocks = httpClient->CallURL(httpClient->GetNFTSLink, "JWT", "Secret", gLMetaverseAPIWrapper->GetNTFSRestCallback);
		stock->GetAllInteroperableWearables(stocks);
		TestEqual("should have a 1 wearable in stock ", stock->GetWearables()->Num(), 1);;
		GLSubSystem->Deinitialize();
	}
	else 
	{
		return false;
	}
	return true;
}

bool FGravityLayerWardrobeCreateFromJson::RunTest(const FString& Parameters)
{
	UMockHTTPClient* httpClient = GEngine->GetEngineSubsystem<UMockHTTPClient>();
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();

	if (httpClient && GLSubSystem)
	{
		UMetaverseAPIWrapper* gLMetaverseAPIWrapper = NewObject<UMetaverseAPIWrapper>();
		gLMetaverseAPIWrapper->InitializeAPIWrapper("apiUrl", "secret");
		UWardrobeByUser* wardrobe = NewObject<UWardrobeByUser>();
		wardrobe->SetWardrobeByUser(gLMetaverseAPIWrapper);
		TestEqual("should have a 0 wearable in wardrobe ", wardrobe->GetWearables()->Num(), 0);;
		FString stocks = httpClient->CallURL(httpClient->GetNFTsByAddressLink, "JWT", "Secret", gLMetaverseAPIWrapper->GetNTFSRestCallback);
		wardrobe->FillWardrobeFromJsonString(stocks);
		TestEqual("should have a 1 wearable in wardrobe ", wardrobe->GetWearables()->Num(), 1);
		GLSubSystem->Deinitialize();
	}
	else
	{
		return false;
	}
	return true;
}

bool FGravityLayerWearableServicesParseWearableData::RunTest(const FString& Parameters) 
{
	UMockHTTPClient* httpClient = GEngine->GetEngineSubsystem<UMockHTTPClient>();
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	if (httpClient) 
	{
		UMetaverseAPIWrapper* gLMetaverseAPIWrapper = NewObject<UMetaverseAPIWrapper>();
		gLMetaverseAPIWrapper->InitializeAPIWrapper("apiUrl", "secret");
		UWearableServices* WearableServices = NewObject<UWearableServices>();
		WearableServices->SetWearableServices(gLMetaverseAPIWrapper);
		FString data = httpClient->CallURL(httpClient->GetModelMetadataByNftLink, "JWT", "Secret", gLMetaverseAPIWrapper->GetModelMetadataByNftCallBack);
		TArray<UGLMetadata*> metadata;
		TestEqual("should have a 0 metadata", metadata.Num(), 0);;
		metadata = WearableServices->GetAllInteroperableWearablesFromData(data);
		TestEqual("should have a 0 metadata", metadata.Num(), 1);
		GLSubSystem->Deinitialize();
	}
	else
		return false;
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS

// Mock HTTP Client
UMockHTTPClient::UMockHTTPClient()
{
}

void UMockHTTPClient::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UMockHTTPClient::Deinitialize()
{
}

FString UMockHTTPClient::CallURL(const FString& URL, const FString& jwt, const FString& secret, FVaRestCallDelegate& Callback)
{
	//UVaRestRequestJSON* response = NewObject<UVaRestRequestJSON>();
	
	if (URL.Equals(GetNFTSLink)) 
	{
		return MockDataCreator::CreateMockWardrobeResult();
	    /*	Callback.Broadcast(response);*/
	}
	else if (URL.Equals(GetNFTsByAddressLink)) {
		return MockDataCreator::CreateMockWardrobeResult();
	}
	else if (URL.Equals(GetModelMetadataByNftLink)) 
	{
		return MockDataCreator::CreteMockNFTData();
	}
	return " ";
}

TArray64<uint8>  UMockHTTPClient::CallImageURL(const FString& URL, FVaRestCallDelegate& Callback)
{
	return MockDataCreator::CreateMockPreviewImageData();
}

TMap<FString, FString> UMockHTTPClient::CreateHeaderParameters(const FString& jwt, const FString& secret)
{
	return TMap<FString, FString>();
}

//void UMockHTTPClient::OnGetNFTsResponseReceived(UVaRestRequestJSON* restRequest)
//{
//	UE_LOG(LogTemp, Warning, TEXT("OnGetNFTsResponseReceived %s"), *restRequest->GetResponseContentAsString());
//}

FString MockDataCreator::CreateMockWardrobeResult()
{
	FString res = "[{\"_id\":\"TestID\", \"name\" : \"TestName\", \"description\" : \"Test Description\", \"images\" : [\"image 1\", \"image 2\"] , \"metadata\" : [{\"metaverseId\":\"TestMEtaverseID\", \"modelUrl\" : \"TestModelURL\", \"previewImage\" : \"PreviewImageLink\", \"attributes\" : [{\"name\":\"Attributtes Name\", \"value\" : \"Attributtes value\"}] }] }]";
	return res;

	//FWardrobeResult wResult;
	//FWardrobeData Wdata = MockDataCreator::CreateMockWardrobeData(); 
	//wResult.products.Add(Wdata);
	//FString code;
	//FJsonObjectConverter::UStructToJsonObjectString(wResult,code);
	//return code;
}

UTexture2D* MockDataCreator::CreateMockPreviewImage()
{
	uint8 TextureWidth = 100;
	uint8 TextureHeight = 128;

	int ArraySize = TextureWidth * TextureHeight * 4;
	TArray<uint8> BGRA8PixelData;
	BGRA8PixelData.Init(255, ArraySize);

	// Create a new transient UTexture2D in a desired pixel format for byte order: B, G, R, A.
	UTexture2D* Texture = UTexture2D::CreateTransient(TextureWidth, TextureHeight, PF_B8G8R8A8);
	// Get a reference to MIP 0, for convenience.
	FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];

	// 2. Memcpy operation.
	// Calculate the number of bytes we will copy.
	const int32 BufferSize = BGRA8PixelData.Num();
	// Mutex lock the MIP's data, not letting any other thread read or write it now.
	void* MipBulkData = Mip.BulkData.Lock(LOCK_READ_WRITE);
	// Pre-allocate enough space to copy our bytes into the MIP's bulk data. 
	Mip.BulkData.Realloc(BufferSize);
	// Copy BufferSize number of bytes starting from BGRA8PixelData's bulk data address in memory to
	// a block of memory starting from the memory address MipBulkData.
	FMemory::Memcpy(MipBulkData, BGRA8PixelData.GetData(), BufferSize);
	// Mutex unlock the MIP's data, letting all other threads read or lock for writing.
	Mip.BulkData.Unlock();

	// 3. Let the engine process new data.
	Texture->UpdateResource();


	return Texture;
}

TArray64<uint8> MockDataCreator::CreateMockPreviewImageData(uint8 TextureWidth, uint8 TextureHeight)
{
	
	TArray<FColor> _imageRawColor;
	for (int i = 0; i < TextureWidth* TextureHeight; i++)
	{
		_imageRawColor.Add(FColor(1,0,0,1));
	}

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);
	ImageWrapper->SetRaw(_imageRawColor.GetData(), _imageRawColor.GetAllocatedSize(), TextureWidth, TextureHeight, ERGBFormat::BGRA, 8);
	const TArray64<uint8>& _ImageData = ImageWrapper->GetCompressed(100);
	return _ImageData;
}

FString MockDataCreator::CreteMockNFTData()
{
	return "[{\"metaverseId\":\"TestMEtaverseID\",\"modelUrl\":\"TestModelURL\",\"previewImage\":\"PreviewImageLink\",\"attributes\":[{\"name\":\"Attributtes Name\",\"value\":\"Attributtes value\"}]}]";

	//FWardrobeData wdata = MockDataCreator::CreateMockWardrobeData();
	//FString code;
	//FJsonObjectConverter::UStructToJsonObjectString(wdata,code);
	//return code;
	
}

FWardrobeData MockDataCreator::CreateMockWardrobeData()
{
	FWardrobeData Wdata;
	Wdata._id = "TestID";
	Wdata.name = "TestName";
	Wdata.description = "Test Description";
	Wdata.images.Add("image 1");
	Wdata.images.Add("image 2");

	FProductMetadata metaData;
	metaData.metaverseId = "TestMEtaverseID";
	metaData.modelUrl = "TestModelURL";
	metaData.previewImage = "PreviewImageLink";

	FMetadataAttributes attributes;
	attributes.name = "Attributtes Name";
	attributes.value = "Attributtes value";

	metaData.attributes.Add(attributes);
	Wdata.metadata.Add(metaData);
	return Wdata;
}
