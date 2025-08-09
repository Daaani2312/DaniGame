#pragma once

#include "CoreMinimal.h"
#include "DaniSwordTypes.generated.h"

// Tipos de estilos de espada
UENUM(BlueprintType)
enum class ESwordStyleType : uint8
{
    SingleKatana      UMETA(DisplayName = "Single Katana"),
    DualKatanas      UMETA(DisplayName = "Dual Katanas"),
    LongSword        UMETA(DisplayName = "Long Sword"),
    SwordAndShield   UMETA(DisplayName = "Sword and Shield"),
    GreatSword       UMETA(DisplayName = "Great Sword"),
    Rapier           UMETA(DisplayName = "Rapier"),
    CustomStyle1     UMETA(DisplayName = "Custom Style 1"),
    CustomStyle2     UMETA(DisplayName = "Custom Style 2")
};

// Tipos de ataques con espada
UENUM(BlueprintType)
enum class ESwordAttackType : uint8
{
    HorizontalSlash,
    VerticalSlash,
    Thrust,
    DiagonalUp,
    DiagonalDown,
    Special1,
    Special2
}; #pragma once
