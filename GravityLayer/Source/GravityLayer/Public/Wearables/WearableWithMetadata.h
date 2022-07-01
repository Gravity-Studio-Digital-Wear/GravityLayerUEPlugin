#pragma once
#include "Wearables\Wearable.h"
#include "Wearables\IWearableWithMetadata.h"
#include "Metadata.h"

class GRAVITYLAYER_API WearableWithMetadata : public IWearableWithMetadata
{
public :
	FString getTitle();
	TArray<UGLMetadata*> getMetadata();

	WearableWithMetadata(FString title)
	{
		Title = title;
		
	}

	WearableWithMetadata(FString title, TArray<UGLMetadata*> metadata)
	{
		Title = title;
		Metadata = metadata;
	}

	virtual ~WearableWithMetadata() 
	{

	}
	void SetMetadata(TArray<UGLMetadata*> metadata)
	{
		Metadata = metadata;
	}
private:
	FString Title;
	TArray<UGLMetadata*> Metadata;
	
};