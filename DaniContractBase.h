#pragma once

#include "CoreMinimal.h"
#include "DaniCombatStyleBase.h"
#include "DaniContractBase.generated.h"

UENUM(BlueprintType)
enum class EContractType : uint8
{
    None,
    Essence,
    Transformation,
    Environment
};

UCLASS(Abstract, Blueprintable)
class DANIGAME_API UDaniContractBase : public UDaniCombatStyleBase
{
    GENERATED_BODY()

public:
    UDaniContractBase();

    // Tipo de contrato
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Contract")
    EContractType ContractType;

    // Nombre del contrato
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Contract")
    FText ContractName;

    // Descripción del contrato
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Contract")
    FText ContractDescription;

    // Inicializar el contrato
    UFUNCTION(BlueprintCallable, Category = "Contract")
    virtual void InitializeContract();

    // Verificar si el usuario está en agua
    UFUNCTION(BlueprintCallable, Category = "Contract")
    bool IsInWater() const;

    // Manejo de stun por agua
    UFUNCTION(BlueprintCallable, Category = "Contract")
    virtual void HandleWaterEffect();

protected:
    // Referencia al componente de stats del personaje
    UPROPERTY()
    class UDaniStatsComponent* StatsComponent;

    // Efectos visuales del contrato
    UPROPERTY(EditDefaultsOnly, Category = "Contract|Effects")
    UParticleSystem* ContractEffect;

    // Componente de efecto activo
    UPROPERTY()
    UParticleSystemComponent* ActiveEffectComponent;
}; #pragma once
