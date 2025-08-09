#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DaniSocialSystem.generated.h"

USTRUCT(BlueprintType)
struct FFamilyData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName FamilyName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    ESocialClass SocialClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float ConquerorWillProbability;
};

UCLASS()
class DANIGAME_API UDaniSocialDatabase : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Families")
    TArray<FFamilyData> Families;
}; #pragma once
