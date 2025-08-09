#pragma once

#include "DaniEssenceBase.h"
#include "DaniFireEssence.generated.h"

UCLASS()
class DANIGAME_API UDaniFireEssence : public UDaniEssenceBase
{
    GENERATED_BODY()

public:
    UDaniFireEssence();

    virtual void InitializeContract() override;
    virtual void ExecuteAbility(int32 AbilityIndex) override;
    virtual void ActivateSpecialMovement() override;
    virtual void DeactivateSpecialMovement() override;
    virtual void UpdateSpecialMovement(float DeltaTime) override;

protected:
    // Habilidades específicas de fuego
    void Fireball();
    void FlameSword();
    void FireShield();
    void Explosion();
    void AreaBurn();
    // (La 6ta es el vuelo, manejado en SpecialMovement)
}; #pragma once
