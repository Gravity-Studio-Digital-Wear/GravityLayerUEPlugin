#pragma once
#include "CoreMinimal.h"
#include "MetaverseEntryPoint.generated.h"

class UMetaverseAPIWrapper;
class UWardrobeByUser;
class UStock;
class UWearableServices;

/// <summary>
/// Metaverse Entry Point is responsible for data storage and collection for linked wearables.
/// </summary>
UCLASS(BlueprintType, Blueprintable)
class GRAVITYLAYER_API UMetaverseEntryPoint : public UObject
{
	GENERATED_BODY()
public :

	UMetaverseEntryPoint();

	/**
	 * @brief SetMetaverseEntryPoint configures metaverse connections. 
	 * @param apiUrl Metaverse api url 
	 * @param secret Metaverse identifier
	 */
	void SetMetaverseEntryPoint(const FString& apiUrl, const FString& secret);
	virtual ~UMetaverseEntryPoint();

	void InitializeEntryPoint(const FString& apiUrl, const FString& secret);
	
	UFUNCTION(BlueprintCallable)
	UMetaverseAPIWrapper* GetGLMetaverseAPIWrapper();

	UFUNCTION(BlueprintCallable)
	UWardrobeByUser* GetWardrobe();

	UFUNCTION(BlueprintCallable)
	UStock* GetStock();

	UFUNCTION(BlueprintCallable)
	UWearableServices* GetWardrobeServices();

private:
 	UMetaverseAPIWrapper* gLMetaverseAPIWrapper = nullptr;
	UWardrobeByUser* wardrobe;
	UStock* stock;
	UWearableServices* wearableServices;
};