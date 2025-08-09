#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DaniRaceSystem.generated.h"

UENUM(BlueprintType)
enum class ERaceType : uint8
{
    Human,
    Giant,
    Oni,
    Aquatic,
    Winged,
    DevilEssence
};

UENUM(BlueprintType)
enum class ESocialClass : uint8
{
    Low,
    Middle,
    High,
    HighMiddle,
    WorldHigh
};

USTRUCT(BlueprintType)
struct FRacialBonus
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StrengthTrainingMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DurabilityTrainingMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SwordTrainingMultiplier = 1.0f;
};

UCLASS()
class DANIGAME_API UDaniRaceData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race")
    ERaceType RaceType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race")
    FRacialBonus BaseRacialBonus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race")
    FRacialBonus RegionalBonus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race")
    FText RaceName;
}; #pragma once
