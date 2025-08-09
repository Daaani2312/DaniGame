#include "DaniRaceComponent.h"
#include "DaniRegionSystem.h"

void UDaniRaceComponent::InitializeRace(ERaceType Race, bool bInIsSamurai)
{
    CurrentRace = Race;
    bIsSamurai = bInIsSamurai;
}

float UDaniRaceComponent::GetTrainingMultiplier(FName StatName, ERegionType CurrentRegion) const
{
    float Multiplier = 1.0f;

    // Aplicar bonus racial base
    switch (CurrentRace)
    {
    case ERaceType::Giant:
        if (StatName == "Strength") Multiplier *= 2.0f;
        break;
    case ERaceType::Oni:
        if (StatName == "Strength" || StatName == "Durability") Multiplier *= 2.0f;
        break;
    case ERaceType::Human:
        if (bIsSamurai && StatName == "Sword" && CurrentRegion == ERegionType::LandOfTheCuttingSun)
            Multiplier *= 2.0f;
        break;
    }

    // Aplicar bonus regional
    switch (CurrentRegion)
    {
    case ERegionType::GiantsRegion:
        if (CurrentRace == ERaceType::Giant && StatName == "Strength")
            Multiplier *= 2.0f;
        break;
    case ERegionType::OniLands:
        if (CurrentRace == ERaceType::Oni &&
            (StatName == "Strength" || StatName == "Durability"))
            Multiplier *= 2.0f;
        break;
    }

    return Multiplier;
}