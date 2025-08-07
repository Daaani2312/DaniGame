#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniStatsStructs.h"
#include "DaniStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, EStatType, StatType, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaExhausted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniStatsComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    // ─── BASE STATS ──────────────────────────────────────────────────
    UPROPERTY(EditDefaultsOnly, Replicated, Category = "Stats")
    FCharacterStats BaseStats;

    // ─── CURRENT STATS ──────────────────────────────────────────────
    UPROPERTY(VisibleAnywhere, Replicated, Category = "Stats")
    float CurrentHealth;

    UPROPERTY(VisibleAnywhere, Replicated, Category = "Stats")
    float CurrentStamina;

    // ─── STAT MODIFIERS ─────────────────────────────────────────────
    UPROPERTY(VisibleInstanceOnly, Category = "Stats")
    float DefenseModifier = 0.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Stats")
    float AttackModifier = 0.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Stats")
    float DodgeChanceModifier = 0.0f;

    UPROPERTY(VisibleInstanceOnly, Category = "Stats")
    float WalkSpeedModifier = 1.0f; // Multiplicativo (1.0 = 100%)

    UPROPERTY(VisibleInstanceOnly, Category = "Stats")
    float SprintSpeedModifier = 1.0f; // Multiplicativo

    // ─── EVENTS ─────────────────────────────────────────────────────
    UPROPERTY(BlueprintAssignable, Category = "Stats|Events")
    FOnStatChanged OnStatChanged;

    UPROPERTY(BlueprintAssignable, Category = "Stats|Events")
    FOnStaminaExhausted OnStaminaExhausted;

    UPROPERTY(BlueprintAssignable, Category = "Stats|Events")
    FOnHealthDepleted OnHealthDepleted;

    // ─── CORE FUNCTIONS ─────────────────────────────────────────────
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ApplyDamage(float DamageAmount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool TryConsumeStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void StartStaminaRegenDelay(float Delay = 2.0f);

    // ─── MODIFIER FUNCTIONS ─────────────────────────────────────────
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddDefenseModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddAttackModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddDodgeChanceModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddWalkSpeedModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddSprintSpeedModifier(float Modifier);

    // ─── GETTERS ───────────────────────────────────────────────────
    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentDefense() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentAttack() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentDodgeChance() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentWalkSpeed() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetCurrentSprintSpeed() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetHealthPercentage() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    float GetStaminaPercentage() const;

    UFUNCTION(BlueprintPure, Category = "Stats")
    bool IsExhausted() const;

private:
    // ─── PRIVATE FUNCTIONS ─────────────────────────────────────────
    void UpdateModifiedStats();
    void RegenerateStamina(float DeltaTime);
    void HandleStaminaExhaustion();
    void OnRegenDelayEnded();
    void RecoverFromExhaustion();

    // ─── TIMERS ────────────────────────────────────────────────────
    FTimerHandle StaminaRegenDelayHandle;
    FTimerHandle ExhaustionRecoveryHandle;

    // ─── STATE ─────────────────────────────────────────────────────
    bool bIsExhausted = false;
    bool bCanRegenStamina = true;
};
