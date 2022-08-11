#pragma once
#include "CoreMinimal.h"
#include "SdkConfiguration.generated.h"

USTRUCT(BlueprintType)
struct GRAVITYLAYER_API FSdkConfiguration
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity SDK COnf")
	FString _account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity SDK COnf")
	FString _apiUrl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gravity SDK COnf")
	FString _secret;
};