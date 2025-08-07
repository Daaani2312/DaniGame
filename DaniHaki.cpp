#include "DaniHakiComponent.h"
#include "DaniStatsComponent.h"
#include "DaniCharacter.h"

UDaniHakiComponent::UDaniHakiComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // Initialize all haki types as inactive
    for (int32 i = 0; i < static_cast<int32>(EHakiType::MAX); ++i)
    {
        ActiveHakiTypes.Add(static_cast<EHakiType>(i), false);
    }
}

void UDaniHakiComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UDaniHakiComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Update haki effects here if needed
}

void UDaniHakiComponent::ActivateArmamentHaki()
{
    if (!ActiveHakiTypes[EHakiType::Armament])
    {
        ActiveHakiTypes[EHakiType::Armament] = true;
        ApplyHakiEffects(EHakiType::Armament, true);
        OnHakiActivated.Broadcast(EHakiType::Armament);
    }
}

void UDaniHakiComponent::ActivateObservationHaki()
{
    if (!ActiveHakiTypes[EHakiType::Observation])
    {
        ActiveHakiTypes[EHakiType::Observation] = true;
        ApplyHakiEffects(EHakiType::Observation, true);
        OnHakiActivated.Broadcast(EHakiType::Observation);
    }
}

void UDaniHakiComponent::ActivateConquerorsHaki()
{
    if (!ActiveHakiTypes[EHakiType::Conquerors])
    {
        ActiveHakiTypes[EHakiType::Conquerors] = true;
        ApplyHakiEffects(EHakiType::Conquerors, true);
        OnHakiActivated.Broadcast(EHakiType::Conquerors);
    }
}

void UDaniHakiComponent::DeactivateHaki(EHakiType HakiType)
{
    if (ActiveHakiTypes[HakiType])
    {
        ActiveHakiTypes[HakiType] = false;
        ApplyHakiEffects(HakiType, false);
        OnHakiDeactivated.Broadcast(HakiType);
    }
}

bool UDaniHakiComponent::IsHakiActive(EHakiType HakiType) const
{
    return ActiveHakiTypes[HakiType];
}

void UDaniHakiComponent::ApplyHakiEffects(EHakiType HakiType, bool bActivate)
{
    ADaniCharacter* OwnerCharacter = Cast<ADaniCharacter>(GetOwner());
    if (!OwnerCharacter || !OwnerCharacter->StatsComponent)
        return;

    switch (HakiType)
    {
    case EHakiType::Armament:
        OwnerCharacter->StatsComponent->SetDefenseModifier(bActivate ? 0.5f : -0.5f);
        break;

    case EHakiType::Observation:
        OwnerCharacter->StatsComponent->SetDodgeChanceModifier(bActivate ? 0.3f : -0.3f);
        break;

    case EHakiType::Conquerors:
        OwnerCharacter->StatsComponent->SetAttackModifier(bActivate ? 0.4f : -0.4f);
        break;

    default:
        break;
    }
}