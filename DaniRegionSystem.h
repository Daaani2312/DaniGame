#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DaniRegionSystem.generated.h"

UENUM(BlueprintType)
enum class ERegionType : uint8
{
    LandOfTheCuttingSun,
    GiantsRegion,
    OniLands,
    AbyssalDepths,
    HighSkies,
    Neutral
};

UCLASS()
class DANIGAME_API UDaniRegionData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Region")
    ERegionType RegionType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Region")
    FText RegionName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Region")
    TArray<ERaceType> AffectedRaces;
}; #pragma once
