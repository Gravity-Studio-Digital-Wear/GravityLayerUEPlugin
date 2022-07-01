#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Interfaces/IHttpRequest.h"
#include <Runtime/Online/HTTP/Public/HttpModule.h>
#include "SdkConfiguration.h"

#include "Subsystems/EngineSubsystem.h"

#include "VaRestJsonObject.h"
#include "VaRestJsonValue.h"
#include "VaRestRequestJSON.h"

#include "VaRestSubsystem.h"

#include "HTTPClient.generated.h"



UCLASS()
class UHTTPClient : public UEngineSubsystem
{
    GENERATED_BODY()
public:
    UHTTPClient();
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
	
public:
    
    void CallURL(const FString& URL, const FString& jwt, const FString& secret, FVaRestCallDelegate& Callback);
    void CallImageURL(const FString& URL, FVaRestCallDelegate& Callback);
};
