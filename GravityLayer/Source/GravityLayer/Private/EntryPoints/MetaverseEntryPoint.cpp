
#include "EntryPoints\MetaverseEntryPoint.h"

#include "Utils\MetaverseAPIWrapper.h"
#include "Wearables\WardrobeByUser.h"
#include "Wearables\WearableServices.h"
#include "Wearables\Stock.h"
#include "Misc/MessageDialog.h"
#include "Logger.h"



void UMetaverseEntryPoint::SetMetaverseEntryPoint(const FString& apiUrl, const FString& secret)
{

    gLMetaverseAPIWrapper = NewObject<UMetaverseAPIWrapper>();
    gLMetaverseAPIWrapper->AddToRoot();
    if(apiUrl.IsEmpty())
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("MetaverseEntryPoint apiUrl is empty.")));

    if (secret.IsEmpty())
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("MetaverseEntryPoint secret is empty.")));

    gLMetaverseAPIWrapper->InitializeAPIWrapper(apiUrl, secret);

    wardrobe = NewObject<UWardrobeByUser>();
    wardrobe->AddToRoot();
    wardrobe->SetWardrobeByUser(gLMetaverseAPIWrapper);

    stock = NewObject<UStock>();
    stock->AddToRoot();
    stock->SetMetaverse(gLMetaverseAPIWrapper);

    wearableServices = NewObject<UWearableServices>();
    wearableServices->AddToRoot();
    wearableServices->SetWearableServices(gLMetaverseAPIWrapper);
    
    UE_LOG(LogTemp, Warning, TEXT("MetaverseEntryPoint::MetaverseEntryPoint"));
}

UMetaverseEntryPoint::UMetaverseEntryPoint()
{
}

UMetaverseEntryPoint::~UMetaverseEntryPoint()
{
    UE_LOG(LogTemp, Warning, TEXT("UMetaverseEntryPoint::~UMetaverseEntryPoint"));

    if(!gLMetaverseAPIWrapper && IsValid(gLMetaverseAPIWrapper))
        gLMetaverseAPIWrapper->RemoveFromRoot();

    if(!wardrobe && IsValid(wardrobe))
        wardrobe->RemoveFromRoot();

    if(!stock && IsValid(stock))
        stock->RemoveFromRoot();

    if(!wearableServices && IsValid(wearableServices))
        wearableServices->RemoveFromRoot();

    /*if(gLMetaverseAPIWrapper)
        free(gLMetaverseAPIWrapper);
    if(wardrobe)
        free(wardrobe);*/
        
}

void UMetaverseEntryPoint::InitializeEntryPoint(const FString& apiUrl, const FString& secret)
{
    SetMetaverseEntryPoint(apiUrl, secret);
}

UMetaverseAPIWrapper* UMetaverseEntryPoint::GetGLMetaverseAPIWrapper()
{
    return gLMetaverseAPIWrapper;
}

UWardrobeByUser* UMetaverseEntryPoint::GetWardrobe()
{
    return wardrobe;
}

UStock* UMetaverseEntryPoint::GetStock()
{
    return stock;
}

UWearableServices* UMetaverseEntryPoint::GetWardrobeServices()
{
    return wearableServices;
}
