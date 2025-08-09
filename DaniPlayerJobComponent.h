#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniJobTypes.h"
#include "DaniPlayerJobComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniPlayerJobComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniPlayerJobComponent();

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
    // Propiedades replicadas
    UPROPERTY(ReplicatedUsing = OnRep_JobData, BlueprintReadOnly, Category = "Job")
    EJobType CurrentJob;

    UPROPERTY(ReplicatedUsing = OnRep_JobData, BlueprintReadOnly, Category = "Job")
    EJobRank CurrentRank;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Job")
    float WorkedHoursToday;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Job")
    float HourlyWage;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Job")
    float CommissionEarned;

    // Funciones Blueprint
    UFUNCTION(BlueprintCallable, Category = "Job")
    void AddWorkedHours(float Hours);

    UFUNCTION(BlueprintCallable, Category = "Job")
    void AddCommission(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Job")
    void PayDailyWages();

    UFUNCTION(BlueprintCallable, Category = "Job")
    bool CanHire() const;

    UFUNCTION(BlueprintCallable, Category = "Job")
    bool CanFire(const UDaniPlayerJobComponent* TargetJobComponent) const;

    UFUNCTION(BlueprintCallable, Category = "Job")
    void SetJobAndRank(EJobType NewJob, EJobRank NewRank);

    // Sistema de salarios base
    static TMap<TPair<EJobType, EJobRank>, float> BaseSalaries;

    UFUNCTION(BlueprintCallable, Category = "Job")
    static float GetBaseSalary(EJobType Job, EJobRank Rank);

private:
    UFUNCTION()
    void OnRep_JobData();

    void CalculateHourlyWage();
};