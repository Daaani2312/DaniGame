#include "DaniCombatComponent.h"
#include "DaniCombatStyleBase.h"
#include "Engine/World.h"

UDaniCombatComponent::UDaniCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicatedByDefault(true);
}

void UDaniCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize with default empty-handed style
    SwitchCombatStyle(UDaniFistStyle::StaticClass());
}

void UDaniCombatComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CleanupCurrentStyle();
    Super::EndPlay(EndPlayReason);
}

void UDaniCombatComponent::CleanupCurrentStyle()
{
    if (CurrentCombatStyle)
    {
        CurrentCombatStyle->OnDeactivated();
        CurrentCombatStyle->DestroyComponent();
        CurrentCombatStyle = nullptr;
    }
}

void UDaniCombatComponent::InitializeNewStyle(TSubclassOf<UDaniCombatStyleBase> StyleClass)
{
    if (!StyleClass || !GetOwner()) return;

    // Create new style component
    CurrentCombatStyle = NewObject<UDaniCombatStyleBase>(this, StyleClass, NAME_None, RF_NoFlags, nullptr, false, nullptr);

    if (CurrentCombatStyle)
    {
        CurrentCombatStyle->RegisterComponent();
        CurrentCombatStyle->OnActivated(GetOwner());

        // Notify about combat mode if active
        if (bCombatModeActive)
        {
            CurrentCombatStyle->OnCombatModeChanged(true);
        }
    }
}

void UDaniCombatComponent::SetCombatMode(bool bEnabled)
{
    if (bCombatModeActive == bEnabled) return;

    bCombatModeActive = bEnabled;

    if (bCombatModeActive)
    {
        OnCombatModeEnabled.Broadcast();
    }
    else
    {
        OnCombatModeDisabled.Broadcast();
    }

    if (CurrentCombatStyle)
    {
        CurrentCombatStyle->OnCombatModeChanged(bCombatModeActive);
    }
}

void UDaniCombatComponent::SwitchCombatStyle(TSubclassOf<UDaniCombatStyleBase> NewStyleClass)
{
    if (!NewStyleClass) return;

    TSubclassOf<UDaniCombatStyleBase> OldStyleClass = GetCurrentStyleClass();

    CleanupCurrentStyle();
    InitializeNewStyle(NewStyleClass);

    OnCombatStyleChanged.Broadcast(OldStyleClass, NewStyleClass);
}

// ─── INPUT INTERFACE ──────────────────────────────────────────────
void UDaniCombatComponent::ExecuteAttack(int32 AttackIndex)
{
    if (CurrentCombatStyle && bCombatModeActive)
    {
        CurrentCombatStyle->ExecuteAttack(AttackIndex);
    }
}

void UDaniCombatComponent::StartBlock()
{
    if (CurrentCombatStyle && bCombatModeActive)
    {
        CurrentCombatStyle->StartBlock();
    }
}

void UDaniCombatComponent::EndBlock()
{
    if (CurrentCombatStyle)
    {
        CurrentCombatStyle->EndBlock();
    }
}

void UDaniCombatComponent::ActivateAbility(int32 AbilityIndex)
{
    if (CurrentCombatStyle && bCombatModeActive)
    {
        CurrentCombatStyle->ActivateAbility(AbilityIndex);
    }
}

void UDaniCombatComponent::ReloadWeapon()
{
    if (CurrentCombatStyle && bCombatModeActive)
    {
        CurrentCombatStyle->ReloadWeapon();
    }
}

TSubclassOf<UDaniCombatStyleBase> UDaniCombatComponent::GetCurrentStyleClass() const
{
    return CurrentCombatStyle ? CurrentCombatStyle->GetClass() : nullptr;
}