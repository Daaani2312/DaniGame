#pragma once

#include "CoreMinimal.h"
#include "DaniJobTypes.generated.h"

UENUM(BlueprintType)
enum class EJobType : uint8
{
    None = 0,

    // Guardianes del Orden
    AdmiralOfTheGuard = 1,
    CorsairCaptain = 2,
    Guardian = 3,
    Cadet = 4,

    // Nobles Mundiales
    NobleHigh = 10,
    NobleMid = 11,
    NobleLow = 12,

    // Trabajos Comerciales
    Blacksmith = 20,
    Fisherman = 21,
    Merchant = 22,
    TravelingVendor = 23,
    Shipwright = 24,
    Cook = 25,
    Rancher = 26,

    // Gremio de Cazarrecompensas
    BountyHunter = 30
};

UENUM(BlueprintType)
enum class EJobRank : uint8
{
    None = 0,

    // Guardianes del Orden
    Admiral = 1,
    Captain = 2,
    Guard = 3,
    Cadet = 4,

    // Nobles Mundiales (sin rangos internos)

    // Comerciales
    Master = 20,
    Journeyman = 21,
    Apprentice = 22
}; #pragma once
