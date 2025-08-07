#pragma once

#include "CoreMinimal.h"
#include "DaniHakiTypes.generated.h"

UENUM(BlueprintType)
enum class EHakiType : uint8
{
    Armament     UMETA(DisplayName = "Armament Haki"),
    Observation  UMETA(DisplayName = "Observation Haki"),
    Conquerors   UMETA(DisplayName = "Conqueror's Haki"),
    MAX          UMETA(Hidden)
};
