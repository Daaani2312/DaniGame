#pragma once

#include "DaniEssenceBase.h"
#include "DaniIceEssence.generated.h"

UCLASS()
class DANIGAME_API UDaniIceEssence : public UDaniEssenceBase
{
    GENERATED_BODY()

public:
    UDaniIceEssence();

    virtual void InitializeContract() override;
    virtual void ExecuteAbility(int32 AbilityIndex) override;
    virtual void ActivateSpecialMovement() override;
    virtual void DeactivateSpecialMovement() override;
    virtual void UpdateSpecialMovement(float DeltaTime) override;

protected:
    // Habilidades específicas de hielo
    void IceSword();
    void IceBall();
    void FreezeArea();
    void IceWall();
    void IceShield();
    // (La 6ta es caminar sobre agua, manejado en SpecialMovement)
}; #pragma once
