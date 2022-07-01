// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/GravityLayerActor.h"
#include "Component/GravityLayerActorComponent.h"
#include "Components/SkeletalMeshComponent.h"



// Sets default values
AGravityLayerActor::AGravityLayerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SetRootComponent(SkeletalMeshComponent);

	GravityLayerComponent = CreateDefaultSubobject<UGravityLayerActorComponent>(TEXT("GravityLayer"));
}

// Called when the game starts or when spawned
void AGravityLayerActor::BeginPlay()
{
	Super::BeginPlay();
}

