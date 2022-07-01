#pragma once

#include "GravityLayerActorComponent.h"
#include "GravityLayerFileLoadComponent.generated.h"



UCLASS(ClassGroup = ("Gravity Layer"), meta = (BlueprintSpawnableComponent))
class GRAVITYLAYER_API UGravityLayerFileLoadComponent : public UActorComponent 
{
	GENERATED_BODY()
public:
	

	UGravityLayerFileLoadComponent();

	UPROPERTY(EditAnywhere, Category = "Gravity Layer")
	FString LoadFromFileRelativePath = "TestCharacter\\RPMGLB\\SomniumPCVR_RPM_texresized.glb";

	UPROPERTY(EditAnywhere, Category = "Gravity Layer")
	USkeleton* avatarSkeleton;

	class USkeletalMeshComponent* skeletalMeshComponent;


	virtual void BeginPlay() override;

	void LoadAssetFromFile();

};