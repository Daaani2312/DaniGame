#pragma once

#include "DaniContractBase.h"
#include "DaniEnvironmentBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DANIGAME_API UDaniEnvironmentBase : public UDaniContractBase
{
    GENERATED_BODY()

public:
    UDaniEnvironmentBase();

    // Habilidades disponibles
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TArray<FName> EnvironmentAbilities;

    // Efectos pasivos
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Environment")
    TArray<FName> PassiveEffects;

    // Ejecutar habilidad
    UFUNCTION(BlueprintCallable, Category = "Environment")
    virtual void ExecuteEnvironmentAbility(int32 AbilityIndex);

    // Activar/desactivar efecto pasivo
    UFUNCTION(BlueprintCallable, Category = "Environment")
    virtual void TogglePassiveEffect(FName EffectName, bool bActivate);
}; #pragma once
