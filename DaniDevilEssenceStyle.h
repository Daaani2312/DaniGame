#pragma once

#include "DaniCombatStyleBase.h"
#include "DaniDevilEssenceStyle.generated.h"

UCLASS()
class DANIGAME_API UDaniDevilFruitStyle : public UDaniCombatStyleBase
{
    GENERATED_BODY()

public:
    virtual void ExecuteAttack_Implementation(int32 AttackIndex) override;
    virtual void ActivateAbility_Implementation(int32 AbilityIndex) override;
    virtual void OnActivated_Implementation(AActor* OwnerActor) override;
    virtual void OnDeactivated_Implementation() override;

private:
    UPROPERTY(EditDefaultsOnly)
    TArray<TSubclassOf<class UDaniFruitPower>> AvailablePowers;

    UPROPERTY()
    UDaniFruitPower* ActivePower = nullptr;

    void ActivatePower(int32 PowerIndex);
    void DeactivatePower();
}; #pragma once
