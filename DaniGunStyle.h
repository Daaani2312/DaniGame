#pragma once

#include "DaniCombatStyleBase.h"
#include "DaniGunStyle.generated.h"

UCLASS()
class DANIGAME_API UDaniGunStyle : public UDaniCombatStyleBase
{
    GENERATED_BODY()

public:
    virtual void ExecuteAttack_Implementation(int32 AttackIndex) override;
    virtual void ReloadWeapon_Implementation() override;
    virtual void OnActivated_Implementation(AActor* OwnerActor) override;

private:
    UPROPERTY()
    class ADaniGunWeapon* EquippedGun = nullptr;

    UPROPERTY(EditDefaultsOnly)
    int32 MaxAmmo = 30;

    UPROPERTY()
    int32 CurrentAmmo = 0;

    void FireWeapon();
    void PlayRecoil();
}; #pragma once
