
#include "GravityLayer.h"
#include "Logger.h"
#include "SdkConfiguration.h"
#include "EntryPoints/MetaverseEntryPoint.h"

#include "Utils\MetaverseAPIWrapper.h"
#include "Wearables\WardrobeByUser.h"
#include "Wearables\WearableServices.h"
#include "Wearables\Stock.h"
#include "Wearables\WearableWithMetadata.h"
#include "Wearables\Metadata.h"
#include <GravityLayer/Public/Utils/HTTPClient.h>


UGravityLayer::UGravityLayer()
{
	UE_LOG(LogTemp, Warning, TEXT("GravityLayer::Initialize"));
}

void UGravityLayer::Initialize(FSubsystemCollectionBase& Collection)
{
	initialized = true;
	this->AddToRoot();
}

void UGravityLayer::Deinitialize()
{
	initialized = false;
	if (!GLMetaverseEntryPoint && IsValid(GLMetaverseEntryPoint)) 
	{
		if(!GLMetaverseEntryPoint->GetStock() && IsValid(GLMetaverseEntryPoint->GetStock()))
			GLMetaverseEntryPoint->GetStock()->OnStockUpdated.RemoveDynamic(this, &UGravityLayer::OnStockUpdate);

		if (!GLMetaverseEntryPoint->GetWardrobe() && IsValid(GLMetaverseEntryPoint->GetWardrobe()))
			GLMetaverseEntryPoint->GetWardrobe()->OnWardrobeUpdated.RemoveDynamic(this, &UGravityLayer::OnWardrobeUpdate);

		if (!GLMetaverseEntryPoint->GetWardrobeServices() && IsValid(GLMetaverseEntryPoint->GetWardrobeServices()))
			GLMetaverseEntryPoint->GetWardrobeServices()->OnWearableMetadataUpdate.RemoveDynamic(this, &UGravityLayer::OnWearableServiceUpdate);

		GLMetaverseEntryPoint->RemoveFromRoot();
	}
		

	GLMetaverseEntryPoint = nullptr;

	if(SDKConf)
		SDKConf.Reset();
	SDKConf = nullptr;
}



void UGravityLayer::Configure()
{
	// SDK Configuration for metaverse end point;
	// TODO: take this configuration to an xml file and lood it at gl module.
	if (!SDKConf) 
	{
		SDKConf = MakeShared<FSdkConfiguration, ESPMode::ThreadSafe>();
		SDKConf->Account = "0x39b7d171e693b3e6270c40899e46c90016e3bd71";
		SDKConf->_apiUrl = "https://gravity-dev.easychain.dev/api";
		//SDKConf->_secret = "4Hf573CnutWhOA3b4yo1H5Sh";
		SDKConf->_secret = "ZrikRzDrFS9jyVX5UBoVLOdD";
		
	}
	// Metaverse enty point setup
	// Entry point events are registered here.
	if (!GLMetaverseEntryPoint) 
	{
		GLMetaverseEntryPoint = NewObject<UMetaverseEntryPoint>();
		GLMetaverseEntryPoint->AddToRoot();
		GLMetaverseEntryPoint->SetMetaverseEntryPoint(SDKConf->_apiUrl, SDKConf->_secret);

		GLMetaverseEntryPoint->GetStock()->OnStockUpdated.AddDynamic(this, &UGravityLayer::OnStockUpdate);
		GLMetaverseEntryPoint->GetWardrobe()->OnWardrobeUpdated.AddDynamic(this, &UGravityLayer::OnWardrobeUpdate);
		GLMetaverseEntryPoint->GetWardrobeServices()->OnWearableMetadataUpdate.AddDynamic(this, &UGravityLayer::OnWearableServiceUpdate);
	}
	
}

bool UGravityLayer::IsInitialized()
{
	return initialized;
}

void UGravityLayer::ConsoleTest()
{
	GetAllInteroperableWearables();
	GetUserInteroperableWearables( SDKConf->Account);
	GetNFTModel("0x2953399124f0cbb46d2cbacd8a89cf0599974963", "75437324160650951662245703982020702172073797313123328702383515790577235918948");
}

void UGravityLayer::GetAllInteroperableWearables()
{
	GLMetaverseEntryPoint->GetStock()->FetchAllInteroperableWearables();
}

void UGravityLayer::GetUserInteroperableWearables( const FString& Account)
{
	GLMetaverseEntryPoint->GetWardrobe()->FetchInteroperableWearables(Account);
}

void UGravityLayer::GetNFTModel(const FString& contractAddress, const FString& tokenId)
{
	GLMetaverseEntryPoint->GetWardrobeServices()->GetWearableMetadata(contractAddress, tokenId);
}

void UGravityLayer::GetNFTModel(const FString& contractAddress, const FString& tokenId, FVaRestCallDelegate& Callback)
{
	GLMetaverseEntryPoint->GetWardrobeServices()->GetWearableMetadata(contractAddress, tokenId,"", Callback);
}

void UGravityLayer::GetglTFLoadAssetFromUrl(const FString& url, FVaRestCallDelegate& Callback)
{
	if (GEngine)
	{
		UHTTPClient* httpClient = GEngine->GetEngineSubsystem<UHTTPClient>();
		httpClient->CallURL(url, "", "", Callback);
	}
}

void UGravityLayer::OnStockUpdate()
{
	int32 wearablesize = GLMetaverseEntryPoint->GetStock()->GetWearables()->Num();
	UE_LOG(LogTemp, Warning, TEXT("Products in stock: %d"), wearablesize);
}

void UGravityLayer::OnWardrobeUpdate()
{
	int32 wearablesize = GLMetaverseEntryPoint->GetWardrobe()->GetWearables()->Num();
	UE_LOG(LogTemp, Warning, TEXT("User's products count: %d"), wearablesize);
}

void UGravityLayer::OnWearableServiceUpdate(TArray<UGLMetadata*> WearableMetadata)
{
	WearableWithMetadata* wearable = new WearableWithMetadata("Fluted Coat");
	wearable->SetMetadata(WearableMetadata);
	
	if (wearable->getMetadata().Num()>0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *wearable->getTitle(), *(wearable->getMetadata()[0]->GetModelUrl()));
		for (auto it = wearable->getMetadata()[0]->GetAttributes()->begin(); it != wearable->getMetadata()[0]->GetAttributes()->end(); ++it)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *it->Key, *it->Value);
		}
	}
}


TArray<UGLMetadata*> UGravityLayer::GetNTFModelData(FString NFTData)
{
	return GLMetaverseEntryPoint->GetWardrobeServices()->GetAllInteroperableWearablesFromData(NFTData);
}

FglTFRuntimeSkeletalMeshConfig UGravityLayer::GetglTFRuntimeSkeletalMeshConfig(FString rootBone, USkeleton* skeleton)
{
	FglTFRuntimeSkeletalMeshConfig skeletonMeshConfig;
	skeletonMeshConfig.SkeletonConfig = GetglTFRuntimeSkeletonConfig(rootBone, skeleton);
	skeletonMeshConfig.MorphTargetsDuplicateStrategy = EglTFRuntimeMorphTargetsDuplicateStrategy::Merge;
	skeletonMeshConfig.MaterialsConfig = GetglTFRuntimeMaterialsConfig();
	if (skeleton)
	{
		skeletonMeshConfig.Skeleton = skeleton;
	}

	return skeletonMeshConfig;

}

FglTFRuntimeSkeletonConfig UGravityLayer::GetglTFRuntimeSkeletonConfig(const FString& rootBoneName, USkeleton* skeleton)
{
	FglTFRuntimeSkeletonConfig glTFRuntimeSkeletonConfig;
	glTFRuntimeSkeletonConfig.CopyRotationsFrom = skeleton;
	glTFRuntimeSkeletonConfig.bAddRootBone = true;
	glTFRuntimeSkeletonConfig.RootBoneName = rootBoneName;
	return glTFRuntimeSkeletonConfig;
}

FglTFRuntimeMaterialsConfig UGravityLayer::GetglTFRuntimeMaterialsConfig()
{
	FglTFRuntimeMaterialsConfig glTFRuntimeMaterialsConfig;
	glTFRuntimeMaterialsConfig.bMergeSectionsByMaterial = true;

	return glTFRuntimeMaterialsConfig;
}

FglTFRuntimeConfig UGravityLayer::GetglTFRuntimeConfig()
{
	FglTFRuntimeConfig runtimeConfig;
	runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;

	return runtimeConfig;
}

USkeletalMeshComponent* UGravityLayer::SetupSkeletalMeshComponent(AActor* targetActor, USkeletalMesh* skeletalMesh)
{
	USkeletalMeshComponent* skeletalMeshComponent = targetActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!skeletalMeshComponent)
	{
		skeletalMeshComponent = AddSkeletalMeshComponent(targetActor);
	}
	skeletalMeshComponent->SetSkeletalMesh(skeletalMesh);

	return skeletalMeshComponent;
}

USkeletalMeshComponent* UGravityLayer::AddSkeletalMeshComponent(AActor* targetActor)
{
	USkeletalMeshComponent* skeletalMeshComponent = NewObject<USkeletalMeshComponent>(targetActor, "Skeletal Mesh");
	skeletalMeshComponent->SetupAttachment(targetActor->GetRootComponent());
	skeletalMeshComponent->RegisterComponent();

	return skeletalMeshComponent;
}
