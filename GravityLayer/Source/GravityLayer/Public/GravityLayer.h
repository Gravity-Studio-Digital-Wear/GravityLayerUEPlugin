// Copyright Gravity Layer, Inc. All Rights Reserved.
#pragma once
// Engine Calls
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Subsystems/EngineSubsystem.h"
#include "Animation/AnimBlueprint.h"
#include "Components/SkeletalMeshComponent.h"

// Json Serialization
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// GLTF Runtime includes
#include "glTFRuntimeParser.h"
#include "glTFRuntimeAsset.h"

// Gravity Layer calls
#include "SdkConfiguration.h"
#include "WearableServiceEvents.h"
#include "EntryPoints/MetaverseEntryPoint.h"


#include "GravityLayer.generated.h"


/// <summary>
/// Gravity Layer plugin enables your game to be connected to linked wearable. 
/// This is the entry point for interoperable cloth nfs.
/// Gravity Layer plugin will be initialized in with game and nft related functions will be called through Gravity layer subsystem.
/// </summary>
UCLASS()
class GRAVITYLAYER_API UGravityLayer : public UEngineSubsystem
{
    GENERATED_BODY()

private:
    bool initialized = false;

    TSharedPtr <FSdkConfiguration> SDKConf = nullptr;
protected:


    UPROPERTY(BlueprintReadOnly)
    UMetaverseEntryPoint* GLMetaverseEntryPoint = nullptr;

    /// <summary>
    /// Cretes Metaverse Enty Points and registers for events
    /// </summary>
    void CreateMetaverseEntyPoint();

    /// <summary>
    /// Cretes Sdk configuration object with given parameters. 
    /// </summary>
    /// <param name="Account"></param>
    /// <param name="ApiUrl"></param>
    /// <param name="Secret"></param>
    void ConfigureSDK(FString Account, FString ApiUrl, FString Secret);
public:

    UGravityLayer();

    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
    
    /// <summary>
    /// Configures Gravity Layer plugin. Creates GLMetaverseEntryPoint object and registers to callbacks for Wardrobe and Stock response.
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    void Configure();

    /// <summary>
    /// Configures plugin with given parameters
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    void ConfigureWithParams(FString Account, FString ApiUrl, FString Secret);
   
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    bool IsInitialized();

    /// <summary>
    /// Test Gravity Layer NTF features
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    void ConsoleTest();

    /**
     * @brief Downloads all nfts
     */
    void GetAllInteroperableWearables();

    /**
     * @brief Downloads Account's NFTs
     * @param Account 
     */
    void GetUserInteroperableWearables(const FString& _account);

    /**
     * @brief Downloads NFT Models
     * @param contractAddress 
     * @param tokenId 
     */
    void GetNFTModel(const FString& contractAddress, const FString& tokenId);


    /**
     * @brief Get NFT Model with callback will download nft model data from server and return it's result to caller.
     * @param contractAddress 
     * @param tokenId  
     * @param Callback 
     */
    void GetNFTModel(const FString& contractAddress, const FString& tokenId, FVaRestCallDelegate& Callback);


    /**
     * @brief Downloads GLTF asset from url
     * @param url 
     * @param Callback 
     */
    void GetglTFLoadAssetFromUrl(const FString& url,  FVaRestCallDelegate& Callback);


    /// <summary>
    /// Called when MetaverseEntryPoint Stock object updated
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer | Event")
    void OnStockUpdate();

    /// <summary>
    /// Called when MetaverseEntryPoint Wardrobe object updated
    /// </summary>
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
    void OnWardrobeUpdate();


    /// <summary>
	/// Called when MetaverseEntryPoint WearableService object updated
	/// </summary>
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer|Event")
    void OnWearableServiceUpdate(TArray<UGLMetadata*> WearableMetadata);

    
	/// <summary>
	/// Creates NFT Model data from string
	/// </summary>
	/// <param name="NFTData">NFT json</param>
	/// <returns>List of NFT metadata</returns>
	UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
	TArray<UGLMetadata*> GetNTFModelData(FString NFTData);

    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    FglTFRuntimeSkeletalMeshConfig GetglTFRuntimeSkeletalMeshConfig(FString rootBone, USkeleton* skeleton);
    
    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    FglTFRuntimeSkeletonConfig GetglTFRuntimeSkeletonConfig(const FString& rootBoneName, USkeleton* skeleton);

    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    FglTFRuntimeMaterialsConfig GetglTFRuntimeMaterialsConfig();

    UFUNCTION(BlueprintCallable, Category = "Gravity Layer")
    FglTFRuntimeConfig GetglTFRuntimeConfig();

    USkeletalMeshComponent* SetupSkeletalMeshComponent(AActor* targetActor, USkeletalMesh* skeletalMesh);

    USkeletalMeshComponent* AddSkeletalMeshComponent(AActor* targetActor);

    FString GetAccountId();
    FString GetApiUrl();
    FString GetSecret();
    UMetaverseEntryPoint* GetMetaverseEntryPoint();
};