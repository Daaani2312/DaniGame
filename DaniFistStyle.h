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

protected:
    // Efectos visuales
    UPROPERTY(EditDefaultsOnly, Category = "Combat|Effects")
    UParticleSystem* FistImpactEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Effects")
    USoundBase* FistImpactSound;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Effects")
    USoundBase* FistWhooshSound;

    // Parámetros de combate
    UPROPERTY(EditDefaultsOnly, Category = "Combat|Parameters")
    float FistRange = 200.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Parameters")
    float BaseDamage = 15.0f;

private:
    void PlayFistCombo(int32 ComboIndex);
    void ApplyFistImpact();
    void SpawnFistTrail();
    void TriggerScreenShake(float Intensity);
    void TriggerHitStop(float Duration);
};