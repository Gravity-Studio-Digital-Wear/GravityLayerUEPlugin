// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GravityLayerActor.generated.h"


UCLASS()
class GRAVITYLAYER_API AGravityLayerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityLayerActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gravity Layer")
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gravity Layer")
	class UGravityLayerActorComponent* GravityLayerComponent;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
};
