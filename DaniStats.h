#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniStatsStructs.h"
#include "DaniStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, EStatType, StatType, float, NewValue);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniStatsComponent();

    UPROPERTY(BlueprintAssignable, Category = "Stats")
    FOnStatChanged OnStatChanged;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    const FCharacterStats& GetBaseStats() const { return BaseStats; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool ConsumeStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    const FCharacterStats& GetModifiedStats() const { return CurrentStats; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    float GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    float GetCurrentStamina() const { return CurrentStamina; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool HasEnoughStamina(float RequiredStamina) const { return CurrentStamina >= RequiredStamina; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetDefenseModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetAttackModifier(float Modifier);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetDodgeChanceModifier(float Modifier);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Stats")
    FCharacterStats BaseStats;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    FCharacterStats CurrentStats;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentHealth;

    UPROPERTY(VisibleAnywhere, Category = "Stats")
    float CurrentStamina;

    UPROPERTY(Transient)
    FTimerHandle ObservationTickHandle;

    UPROPERTY(EditDefaultsOnly, Category = "Haki|Balance")
    float ObservationTickInterval = 0.2f;

    void UpdateStats();
    void RegenerateStamina(float DeltaTime);
}
