#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "WearableServiceEvents.h"
#include "GravityLayerActorComponent.generated.h"

class UAnimBlueprint;
class USkeleton;
class UglTFRuntimeAsset;



UCLASS()
/// <summary>
/// GravityLayerActorComponent should be added to actors which will display an NFT
/// </summary>
class GRAVITYLAYER_API UGravityLayerActorComponent : public UActorComponent {
	GENERATED_BODY()
public:
	UGravityLayerActorComponent();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate OnWearableLoadedResponse;

	UPROPERTY(BlueprintCallable, Category = "Gravity Layer|Event")
	FVaRestCallDelegate OnglTFLoadAssetFromUrlResponse;
public:

	UPROPERTY(EditAnywhere, Category = "Gravity Layer")
	USkeleton* avatarSkeleton;

	class USkeletalMeshComponent* skeletalMeshComponent;

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void GetModelRequestResponse(UVaRestRequestJSON* Request);

	UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
	void GetglTFLoadAssetFromUrlResponse(UVaRestRequestJSON* Request);

	FglTFRuntimeHttpResponse onGltfRuntimeHttpResponse;

	FglTFRuntimeSkeletalMeshAsync onSkeletalMeshCallback;

private :
	TArray<UGLMetadata*> glData;

private:
	
	void LoadAssetFromUrl();

	UFUNCTION()
	void OnAssetLoaded(UglTFRuntimeAsset* asset);

	void LoadSkeletalMesh(UglTFRuntimeAsset* asset);

	UFUNCTION()
	void OnSkeletalMeshLoaded(USkeletalMesh* skeletalMesh);
};