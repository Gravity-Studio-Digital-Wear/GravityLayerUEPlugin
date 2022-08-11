#include "Utils/HTTPClient.h"
#include "VaRestJsonObject.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Logger.h"



UHTTPClient::UHTTPClient()
	: UAHTTPCLient()
{
}

void UHTTPClient::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UHTTPClient::Deinitialize()
{
	Super::Deinitialize();
}

void UHTTPClient::CallURL(const FString& URL, const FString& jwt, const FString& secret, FVaRestCallDelegate& Callback)
{
	UVaRestSubsystem* restSubSystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	UVaRestJsonObject* VaRestJson = NewObject<UVaRestJsonObject>();
	TMap<FString, FString> headerParameters = CreateHeaderParameters(jwt, secret);
	restSubSystem->CallURL(URL, headerParameters, EVaRestRequestVerb::GET, EVaRestRequestContentType::json, VaRestJson, Callback);
}

void UHTTPClient::CallImageURL(const FString& URL, FVaRestCallDelegate& Callback)
{
	UVaRestSubsystem* restSubSystem = GEngine->GetEngineSubsystem<UVaRestSubsystem>();
	UVaRestJsonObject* VaRestJson = NewObject<UVaRestJsonObject>();
	TMap<FString, FString> headerParameters;

	restSubSystem->CallURL(URL, headerParameters, EVaRestRequestVerb::GET, EVaRestRequestContentType::binary, VaRestJson, Callback);
}

TMap<FString, FString> UHTTPClient::CreateHeaderParameters(const FString& jwt, const FString& secret)
{
	TMap<FString, FString> headerParameters;
	if (jwt.Len() > 0)
	{
		headerParameters.Add("Authorization", "Bearer " + jwt);
	}
	if (secret.Len() > 0)
	{
		headerParameters.Add("api-key", secret);
	}
	return headerParameters;
}
