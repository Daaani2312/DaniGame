#include "DaniCombatStyleBase.h"

UDaniCombatStyleBase::UDaniCombatStyleBase()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UDaniCombatStyleBase::OnActivated_Implementation(AActor* OwnerActor)
{
    CombatOwner = OwnerActor;
}

void UDaniCombatStyleBase::OnDeactivated_Implementation()
{
    // Cleanup logic in child classes
}

void UDaniCombatStyleBase::OnCombatModeChanged_Implementation(bool bEnabled)
{
    // React to combat mode changes
}

// Default implementations do nothing
void UDaniCombatStyleBase::ExecuteAttack_Implementation(int32 AttackIndex) {}
void UDaniCombatStyleBase::StartBlock_Implementation() {}
void UDaniCombatStyleBase::EndBlock_Implementation() {}
void UDaniCombatStyleBase::ActivateAbility_Implementation(int32 AbilityIndex) {}
void UDaniCombatStyleBase::ReloadWeapon_Implementation() {}