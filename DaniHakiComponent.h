#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniStatsStructs.h"
#include "DaniStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, EStatType, StatType, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatStatChanged, FCombatStat, ChangedStat);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniStatsComponent();

    // Delegados
    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnStatChanged OnStatChanged;

    UPROPERTY(BlueprintAssignable, Category = "Stats|Combat")
    FOnCombatStatChanged OnCombatStatChanged;

    // Niveles de habilidad
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Levels")
    int32 SwordLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Levels")
    int32 GunLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Levels")
    int32 DevilEssenceLevel = 1;

    // Stats base
    UFUNCTION(BlueprintCallable, Category = "Stats")
    const FCharacterStats& GetBaseStats() const { return BaseStats; }

    // Stats modificadas (con buffs/debuffs)
    UFUNCTION(BlueprintCallable, Category = "Stats")
    const FCharacterStats& GetModifiedStats() const { return CurrentStats; }

    // Manejo de stamina
    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool ConsumeStamina(float Amount);

    // Modificadores de stats
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddAttackModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddDefenseModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddDodgeModifier(float Modifier);

    // Getters
    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentStamina() const { return CurrentStamina; }

    UFUNCTION(BlueprintPure, Category = "Stats")
    bool HasEnoughStamina(float RequiredStamina) const;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // Stats base (configurables en editor)
    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    FCharacterStats BaseStats;

    // Stats actuales (con modificadores)
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    FCharacterStats CurrentStats;

    // Valores actuales
    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentHealth;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentStamina;

    // Modificadores acumulativos
    float TotalAttackModifier = 0.0f;
    float TotalDefenseModifier = 0.0f;
    float TotalDodgeModifier = 0.0f;

    // Temporizador para regeneración
    FTimerHandle RegenerationTimerHandle;

    // Actualizar stats con modificadores
    void UpdateStats();

    // Regenerar stamina
    void RegenerateStamina(float DeltaTime);
};