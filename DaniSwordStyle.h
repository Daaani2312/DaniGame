#pragma once

#include "DaniCombatStyleBase.h"
#include "DaniSwordStyle.generated.h"

UCLASS()
class DANIGAME_API UDaniSwordStyle : public UDaniCombatStyleBase
{
    GENERATED_BODY()

public:
    virtual void ExecuteAttack_Implementation(int32 AttackIndex) override;
    virtual void StartBlock_Implementation() override;
    virtual void EndBlock_Implementation() override;
    virtual void OnActivated_Implementation(AActor* OwnerActor) override;

private:
    UPROPERTY()
    class ADaniSwordWeapon* EquippedSword = nullptr;

    void PlaySwordSwing(int32 SwingType);
    void CheckSwordHit();
}; #pragma once
