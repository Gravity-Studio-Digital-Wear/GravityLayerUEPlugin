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

UCLASS(Abstract)
class UAHTTPCLient : public UEngineSubsystem
{
    GENERATED_BODY()
public :
    virtual void CallURL(const FString& URL, const FString& jwt, const FString& secret, FVaRestCallDelegate& Callback) {};
    virtual void CallImageURL(const FString& URL, FVaRestCallDelegate& Callback) {};
    virtual TMap<FString, FString> CreateHeaderParameters(const FString& jwt, const FString& secret) {
        return  TMap<FString, FString>();
    };

};

UCLASS()
class UHTTPClient : public UAHTTPCLient
{
    GENERATED_BODY()
public:
    UHTTPClient();
    // Begin USubsystem
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
	
public:
    
    void CallURL(const FString& URL, const FString& jwt, const FString& secret, FVaRestCallDelegate& Callback) override ;
    void CallImageURL(const FString& URL, FVaRestCallDelegate& Callback) override;
    TMap<FString, FString> CreateHeaderParameters(const FString& jwt, const FString& secret) override ;

};
