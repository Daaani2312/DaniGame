#include "DaniCombatComponent.h"
#include "DaniCombatStyleBase.h"

UDaniCombatComponent::UDaniCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UDaniCombatComponent::BeginPlay()
{
    Super::BeginPlay();

    // Inicializar con estilo por defecto (mano vacía)
    SwitchCombatStyle(UDaniFistStyle::StaticClass());
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
    CurrentCombatStyle = NewObject<UDaniCombatStyleBase>(this, StyleClass);
    CurrentCombatStyle->RegisterComponent();
    CurrentCombatStyle->OnActivated(GetOwner());

    if (bCombatModeActive)
    {
        CurrentCombatStyle->OnCombatModeChanged(true);
    }
}

// ??? INPUT INTERFACE ???????????????????????????????????????????????
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