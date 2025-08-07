#pragma once

#include "CoreMinimal.h"
#include "DaniHakiTypes.generated.h"

UENUM(BlueprintType)
enum class EEnergyType : uint8
{
    ArmorEnergy      UMETA(DisplayName = "Armor Energy"),
    SenseEnergy      UMETA(DisplayName = "Sense Energy"),
    WillEnergy       UMETA(DisplayName = "Will Energy"),
    MAX              UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FEnergyLevelData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    int32 XPToNextLevel = 10;

    UPROPERTY(EditDefaultsOnly)
    float BaseStaminaCost = 0.0f;

    UPROPERTY(EditDefaultsOnly)
    float CooldownDuration = 0.0f;

    UPROPERTY(EditDefaultsOnly)
    float ActiveDuration = 0.0f;
};