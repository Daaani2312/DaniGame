#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniCombatTypes.h"
#include "DaniCombatStyleBase.generated.h"

class UDaniStatsComponent;
class UAnimMontage;

/**
 * Componente base para todos los estilos de combate del juego.
 * Proporciona interfaz común y funcionalidad base para sistemas de combate.
 */
UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup = (Combat), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniCombatStyleBase : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniCombatStyleBase();

    //~ Begin Activation Interface
    UFUNCTION(BlueprintCallable, Category = "Combat|Activation")
    virtual void ActivateStyle(bool bReset = false) override;

    UFUNCTION(BlueprintCallable, Category = "Combat|Activation")
    virtual void DeactivateStyle();
    //~ End Activation Interface

    //~ Begin Combat Interface
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void EnterCombatMode();
    virtual void EnterCombatMode_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
    void ExitCombatMode();
    virtual void ExitCombatMode_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Attack")
    void ExecuteAttack(int32 AttackIndex);
    virtual void ExecuteAttack_Implementation(int32 AttackIndex);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Defense")
    void StartBlocking();
    virtual void StartBlocking_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Defense")
    void EndBlocking();
    virtual void EndBlocking_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Abilities")
    void ActivateAbility(int32 AbilityIndex);
    virtual void ActivateAbility_Implementation(int32 AbilityIndex);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat|Weapons")
    void ReloadWeapon();
    virtual void ReloadWeapon_Implementation();
    //~ End Combat Interface

    //~ Begin Getters
    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsInCombatMode() const { return bInCombatMode; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsBlocking() const { return bIsBlocking; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    AActor* GetCombatOwner() const { return CombatOwner; }
    //~ End Getters

protected:
    //~ Begin Component Interface
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    //~ End Component Interface

    // Propiedades del combate
    UPROPERTY(Transient)
    AActor* CombatOwner;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat|State")
    bool bInCombatMode;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat|State")
    bool bIsBlocking;

    // Referencia al componente de stats
    UPROPERTY(Transient)
    UDaniStatsComponent* StatsComponent;

    // Configuración de animaciones
    UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
    TMap<int32, UAnimMontage*> AttackMontages;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
    UAnimMontage* BlockStartMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Animation")
    UAnimMontage* BlockEndMontage;

    // Efectos
    UPROPERTY(EditDefaultsOnly, Category = "Combat|Effects")
    UParticleSystem* CombatStartEffect;

    UPROPERTY(EditDefaultsOnly, Category = "Combat|Effects")
    UParticleSystem* CombatEndEffect;

private:
    // Helper para obtener el character
    class ACharacter* GetOwnerCharacter() const;
};