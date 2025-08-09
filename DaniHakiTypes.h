#pragma once

#include "CoreMinimal.h"
#include "DaniHakiTypes.generated.h"

UENUM(BlueprintType)
enum class EHakiType : uint8
{
    Armament,
    Observation,
    Conquerors,
    MAX
};

UENUM(BlueprintType)
enum class EHakiLevel : uint8
{
    Level1,
    Level2,
    Level3
};

USTRUCT(BlueprintType)
struct FHakiLevelData
{
    GENERATED_BODY()

    // XP requerido para alcanzar este nivel
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 XPRequired = 0;

    // Modificadores de stats
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float AttackModifier = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DefenseModifier = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float DodgeModifier = 0.0f;

    // Beneficios específicos para tiradores
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float RecoilReduction = 0.0f; // Porcentaje de reducción de retroceso

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float AimAssistStrength = 0.0f; // Fuerza del aim assist

    // Costos y duraciones
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float StaminaCostPerSecond = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseDuration = 0.0f;
};

USTRUCT(BlueprintType)
struct FHakiProgress
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    EHakiLevel CurrentLevel = EHakiLevel::Level1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 CurrentXP = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bIsUnlocked = false;
};