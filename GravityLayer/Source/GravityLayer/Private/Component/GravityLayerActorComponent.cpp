#include "Component\GravityLayerActorComponent.h"
#include "GravityLayer.h"


UGravityLayerActorComponent::UGravityLayerActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGravityLayerActorComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* thisActor = this->GetOwner();
	// Get NFT Data 
	if (GEngine) 
	{
		UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
		OnWearableLoadedResponse.AddDynamic(this, &UGravityLayerActorComponent::GetModelRequestResponse);
		if (GLSubSystem && IsValid(GLSubSystem)) 
		{
			//75437324160650951662245703982020702172073797313123328702383515790577235918948 // rpm avatar
			// 75437324160650951662245703982020702172073797313123328702383515791676747546724 // hoodie
			GLSubSystem->GetNFTModel("0x2953399124F0cBB46d2CbACD8A89cF0599974963",
				"75437324160650951662245703982020702172073797313123328702383515790577235918948", OnWearableLoadedResponse);
		}
	}
	
	skeletalMeshComponent = thisActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!skeletalMeshComponent || !IsValid(skeletalMeshComponent)) 
	{
		skeletalMeshComponent = NewObject<USkeletalMeshComponent>(thisActor,FName("Skeletal Mesh"));
		skeletalMeshComponent->SetupAttachment(thisActor->GetRootComponent());
		skeletalMeshComponent->RegisterComponent();
	}

	onGltfRuntimeHttpResponse.BindUFunction(this, "LoadSkeletalMesh");
	onSkeletalMeshCallback.BindUFunction(this, "OnSkeletalMeshLoaded");
	OnglTFLoadAssetFromUrlResponse.AddDynamic(this, &UGravityLayerActorComponent::GetglTFLoadAssetFromUrlResponse);
}

void UGravityLayerActorComponent::GetModelRequestResponse(UVaRestRequestJSON* Request)
{
	OnWearableLoadedResponse.RemoveDynamic(this, &UGravityLayerActorComponent::GetModelRequestResponse);
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	FString response = Request->GetResponseContentAsString();
	glData = GLSubSystem->GetNTFModelData(response);
	
	UE_LOG(LogTemp, Warning, TEXT("UGravityLayerActorComponent::GetModelRequestResponse %d"), glData.Num());
	LoadAssetFromUrl();
}



void UGravityLayerActorComponent::LoadAssetFromUrl()
{
	FJsonSerializableKeyValueMap headers;
	if (GEngine)
	{
		UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
		if(glData.Num()>0 && !glData[0]->GetModelUrl().IsEmpty())
			GLSubSystem->GetglTFLoadAssetFromUrl(glData[0]->GetModelUrl(), OnglTFLoadAssetFromUrlResponse);
	}
}

void UGravityLayerActorComponent::GetglTFLoadAssetFromUrlResponse(UVaRestRequestJSON* Request)
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	UglTFRuntimeAsset* Asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromData(Request->GetResponseContent(), GLSubSystem->GetglTFRuntimeConfig());
	OnAssetLoaded(Asset);
}


void UGravityLayerActorComponent::OnAssetLoaded(UglTFRuntimeAsset* asset)
{
	LoadSkeletalMesh(asset);
}

void UGravityLayerActorComponent::LoadSkeletalMesh(UglTFRuntimeAsset* asset)
{
	FString rootBone = "Armature";
	FJsonSerializableArray excludeNodes;
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();

	asset->LoadSkeletalMeshRecursiveAsync(rootBone, excludeNodes,
		onSkeletalMeshCallback, GLSubSystem->GetglTFRuntimeSkeletalMeshConfig(rootBone, avatarSkeleton));
}

void UGravityLayerActorComponent::OnSkeletalMeshLoaded(USkeletalMesh* skeletalMesh)
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	skeletalMeshComponent = GLSubSystem->SetupSkeletalMeshComponent(this->GetOwner(), skeletalMesh);
}
