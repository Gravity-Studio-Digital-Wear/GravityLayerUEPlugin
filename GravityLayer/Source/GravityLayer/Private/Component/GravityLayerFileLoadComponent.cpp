#include "Component\GravityLayerFileLoadComponent.h"
#include "GravityLayer.h"

UGravityLayerFileLoadComponent::UGravityLayerFileLoadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGravityLayerFileLoadComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* thisActor = this->GetOwner();

	skeletalMeshComponent = thisActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!skeletalMeshComponent || !IsValid(skeletalMeshComponent))
	{
		skeletalMeshComponent = NewObject<USkeletalMeshComponent>(thisActor, FName("Skeletal Mesh"));
		skeletalMeshComponent->SetupAttachment(thisActor->GetRootComponent());
		skeletalMeshComponent->RegisterComponent();
	}
	LoadAssetFromFile();
}

void UGravityLayerFileLoadComponent::LoadAssetFromFile()
{
	UGravityLayer* GLSubSystem = GEngine->GetEngineSubsystem<UGravityLayer>();
	FString TruePath = FPaths::Combine(FPaths::ProjectDir(), LoadFromFileRelativePath);
	UglTFRuntimeAsset* Asset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(TruePath,
		false, 
		GLSubSystem->GetglTFRuntimeConfig());

	FString rootBone = "Armature";
	FJsonSerializableArray excludeNodes;
	USkeletalMesh* skeletalMesh = Asset->LoadSkeletalMeshRecursive(rootBone, excludeNodes, GLSubSystem->GetglTFRuntimeSkeletalMeshConfig(rootBone, avatarSkeleton));
	skeletalMeshComponent = GLSubSystem->SetupSkeletalMeshComponent(this->GetOwner(), skeletalMesh);
}
