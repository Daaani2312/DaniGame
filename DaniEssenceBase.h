#pragma once

#include "DaniContractBase.h"
#include "DaniEssenceBase.generated.h"

UENUM(BlueprintType)
enum class EEssenceType : uint8
{
    None,
    Fire,
    Ice,
    Light
};

USTRUCT(BlueprintType)
struct FEssenceAbility
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;
};

UCLASS(Abstract, Blueprintable)
class DANIGAME_API UDaniEssenceBase : public UDaniContractBase
{
    GENERATED_BODY()

public:
    UDaniEssenceBase();

    // Tipo de esencia
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Essence")
    EEssenceType EssenceType;

    // Habilidades disponibles (0-4 normales, 5 es movimiento especial)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essence")
    TArray<FEssenceAbility> Abilities;

    // Inmunidades y vulnerabilidades
    UFUNCTION(BlueprintCallable, Category = "Essence")
    virtual bool IsImmuneToNormalAttacks() const;

    UFUNCTION(BlueprintCallable, Category = "Essence")
    virtual float GetDamageReductionAgainstAllies() const;

    // Habilidades
    UFUNCTION(BlueprintCallable, Category = "Essence")
    virtual void ExecuteAbility(int32 AbilityIndex);

    // Movimiento especial
    UFUNCTION(BlueprintCallable, Category = "Essence")
    virtual void ActivateSpecialMovement();

    UFUNCTION(BlueprintCallable, Category = "Essence")
    virtual void DeactivateSpecialMovement();

    UFUNCTION(BlueprintCallable, Category = "Essence")
    virtual void UpdateSpecialMovement(float DeltaTime);

protected:
    // Estado del movimiento especial
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Essence")
    bool bSpecialMovementActive;

    // Efectos visuales del movimiento especial
    UPROPERTY(EditDefaultsOnly, Category = "Essence|Effects")
    UParticleSystem* SpecialMovementEffect;
}; #pragma once
