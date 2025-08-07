#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniCombatStyleBase.generated.h"

UCLASS(Abstract)
class DANIGAME_API UDaniCombatStyleBase : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniCombatStyleBase();

    // ??? COMBAT INTERFACE ??????????????????????????????????????????
    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void OnActivated(AActor* OwnerActor);
    virtual void OnActivated_Implementation(AActor* OwnerActor);

    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void OnDeactivated();
    virtual void OnDeactivated_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void OnCombatModeChanged(bool bEnabled);
    virtual void OnCombatModeChanged_Implementation(bool bEnabled);

    // ??? COMBAT ACTIONS ???????????????????????????????????????????
    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void ExecuteAttack(int32 AttackIndex);
    virtual void ExecuteAttack_Implementation(int32 AttackIndex);

    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void StartBlock();
    virtual void StartBlock_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void EndBlock();
    virtual void EndBlock_Implementation();

    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void ActivateAbility(int32 AbilityIndex);
    virtual void ActivateAbility_Implementation(int32 AbilityIndex);

    UFUNCTION(BlueprintNativeEvent, Category = "Combat Style")
    void ReloadWeapon();
    virtual void ReloadWeapon_Implementation();

protected:
    UPROPERTY(Transient)
    TWeakObjectPtr<AActor> CombatOwner;
}; #pragma once
