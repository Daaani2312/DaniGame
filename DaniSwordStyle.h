#pragma once

#include "CoreMinimal.h"
#include "DaniCombatStyleBase.h"
#include "DaniSwordTypes.h"
#include "DaniSwordStyle.generated.h"

class ADaniSwordWeapon;
class UAnimMontage;

// Estructura para definir variantes de estilo de espada
USTRUCT(BlueprintType)
struct FSwordStyleVariant
{
    GENERATED_BODY()

    // Tipo de estilo (1 katana, 2 katanas, espada larga, etc.)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESwordStyleType StyleType;

    // Animaciones de ataque para este estilo
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<UAnimMontage*> AttackAnimations;

    // Animación de bloqueo
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* BlockAnimation;

    // Modificador de daño para este estilo
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier = 1.0f;

    // Modificador de velocidad de ataque
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpeedMultiplier = 1.0f;

    // Efecto visual específico del estilo
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UParticleSystem* StyleEffect;
};

UCLASS(Blueprintable, BlueprintType)
class DANIGAME_API UDaniSwordStyle : public UDaniCombatStyleBase
{
    GENERATED_BODY()

public:
    UDaniSwordStyle();

    //~ Begin UDaniCombatStyleBase Interface
    virtual void ExecuteAttack_Implementation(int32 AttackIndex) override;
    virtual void StartBlock_Implementation() override;
    virtual void EndBlock_Implementation() override;
    virtual void OnActivated_Implementation(AActor* OwnerActor) override;
    virtual void OnDeactivated_Implementation() override;
    //~ End UDaniCombatStyleBase Interface

    // Cambiar estilo de espada
    UFUNCTION(BlueprintCallable, Category = "Sword Style")
    void ChangeSwordStyle(ESwordStyleType NewStyle);

    // Obtener estilo actual
    UFUNCTION(BlueprintPure, Category = "Sword Style")
    ESwordStyleType GetCurrentStyle() const { return CurrentStyle; }

protected:
    // Estilo actual de espada
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sword Style")
    ESwordStyleType CurrentStyle;

    // Variantes de estilo configuradas
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sword Style")
    TArray<FSwordStyleVariant> StyleVariants;

    // Espada equipada
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sword Style")
    ADaniSwordWeapon* EquippedSword;

    // Efecto actual del estilo
    UPROPERTY()
    UParticleSystemComponent* ActiveStyleEffect;

private:
    // Reproducir animación de ataque con espada
    void PlaySwordSwing(int32 SwingType);

    // Verificar golpe de espada
    void CheckSwordHit();

    // Obtener variante de estilo actual
    const FSwordStyleVariant* GetCurrentStyleVariant() const;

    // Configurar efectos visuales del estilo
    void SetupStyleEffects();

    // Configurar arma según el estilo
    void SetupWeaponForStyle();
};