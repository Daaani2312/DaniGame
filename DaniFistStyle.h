#pragma once

#include "DaniCombatStyleBase.h"
#include "DaniFistStyle.generated.h"

UCLASS()
class DANIGAME_API UDaniFistStyle : public UDaniCombatStyleBase
{
    GENERATED_BODY()

public:
    virtual void ExecuteAttack_Implementation(int32 AttackIndex) override;
    virtual void StartBlock_Implementation() override;
    virtual void EndBlock_Implementation() override;

private:
    void PlayFistCombo(int32 ComboIndex);
    void ApplyFistImpact();
}; #pragma once
