#pragma once

#include "DaniEssenceBase.h"
#include "DaniLightEssence.generated.h"

UCLASS()
class DANIGAME_API UDaniLightEssence : public UDaniEssenceBase
{
    GENERATED_BODY()

public:
    UDaniLightEssence();

    virtual void InitializeContract() override;
    virtual void ExecuteAbility(int32 AbilityIndex) override;
    virtual void ActivateSpecialMovement() override;
    virtual void DeactivateSpecialMovement() override;
    virtual void UpdateSpecialMovement(float DeltaTime) override;

protected:
    // Habilidades específicas de luz
    void LightBeam();
    void BlindingFlash();
    void LaserFocus();
    void HealingAura();
    void LightShield();
    // (La 6ta es vuelo en línea recta, manejado en SpecialMovement)
}; #pragma once
