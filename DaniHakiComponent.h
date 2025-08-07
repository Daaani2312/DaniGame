#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniHakiTypes.h"
#include "DaniHakiComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHakiActivated, EHakiType, HakiType, float, StaminaCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHakiDeactivated, EHakiType, HakiType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHakiLevelUp, EHakiType, HakiType, int32, NewLevel);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniHakiComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniHakiComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    // ─── HAKI CONTROL ─────────────────────────────────────────────────
    UFUNCTION(BlueprintCallable, Category = "Haki")
    bool TryActivateHaki(EHakiType HakiType);

    UFUNCTION(BlueprintCallable, Category = "Haki")
    void DeactivateHaki(EHakiType HakiType);

    UFUNCTION(BlueprintCallable, Category = "Haki")
    bool IsHakiActive(EHakiType HakiType) const;

    // ─── PROGRESSION ─────────────────────────────────────────────────
    UFUNCTION(BlueprintCallable, Category = "Haki")
    int32 GetHakiLevel(EHakiType HakiType) const;

    UFUNCTION(BlueprintCallable, Category = "Haki")
    int32 GetHakiUsageCount(EHakiType HakiType) const;

    // ─── EVENTS ──────────────────────────────────────────────────────
    UPROPERTY(BlueprintAssignable, Category = "Haki|Events")
    FOnHakiActivated OnHakiActivated;

    UPROPERTY(BlueprintAssignable, Category = "Haki|Events")
    FOnHakiDeactivated OnHakiDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Haki|Events")
    FOnHakiLevelUp OnHakiLevelUp;

private:
    // ─── HAKI STATE ──────────────────────────────────────────────────
    UPROPERTY(Replicated)
    TMap<EHakiType, int32> HakiUsageCounts;

    UPROPERTY(Replicated)
    TMap<EHakiType, int32> HakiLevels;

    UPROPERTY(Replicated)
    TMap<EHakiType, bool> ActiveHakis;

    UPROPERTY(Transient)
    TMap<EHakiType, float> HakiCooldowns;

    // ─── TIMERS ──────────────────────────────────────────────────────
    FTimerHandle ConquerorsTimerHandle;
    FTimerHandle ObservationTickHandle;

    // ─── REFERENCES ──────────────────────────────────────────────────
    UPROPERTY(Transient)
    TWeakObjectPtr<ADaniCharacter> OwnerCharacter;

    UPROPERTY(Transient)
    TWeakObjectPtr<UDaniStatsComponent> StatsComponent;

    // ─── CONFIGURABLES ───────────────────────────────────────────────
    UPROPERTY(EditDefaultsOnly, Category = "Haki|Balance", meta = (ClampMin = 1))
    int32 MaxLevel = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Haki|Balance")
    float ConquerorsMaxDuration = 30.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Haki|Balance")
    float ObservationTickInterval = 0.2f;

    // ─── PRIVATE FUNCTIONS ───────────────────────────────────────────
    void OnObservationTick();
    void DeactivateConquerorsHaki();

    void IncreaseHakiUsage(EHakiType HakiType);
    void CheckLevelUp(EHakiType HakiType);

    float GetStaminaCostForHaki(EHakiType HakiType) const;
    float GetCooldownForHaki(EHakiType HakiType) const;
    int32 GetXPToNextLevel(int32 CurrentLevel) const;
};