#include "DaniPlayerJobComponent.h"
#include "PJ1.h" // Tu clase de personaje principal
#include "Net/UnrealNetwork.h"

// Inicializar salarios base
TMap<TPair<EJobType, EJobRank>, float> UDaniPlayerJobComponent::BaseSalaries = {
    // Guardianes del Orden
    {TPair<EJobType, EJobRank>(EJobType::AdmiralOfTheGuard, EJobRank::Admiral), 500.0f},
    {TPair<EJobType, EJobRank>(EJobType::CorsairCaptain, EJobRank::Captain), 300.0f},
    // ... otros salarios
};

UDaniPlayerJobComponent::UDaniPlayerJobComponent()
{
    SetIsReplicatedByDefault(true);
    CurrentJob = EJobType::None;
    CurrentRank = EJobRank::None;
    WorkedHoursToday = 0.0f;
    CommissionEarned = 0.0f;
    HourlyWage = 0.0f;
}

void UDaniPlayerJobComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UDaniPlayerJobComponent, CurrentJob);
    DOREPLIFETIME(UDaniPlayerJobComponent, CurrentRank);
    DOREPLIFETIME(UDaniPlayerJobComponent, WorkedHoursToday);
    DOREPLIFETIME(UDaniPlayerJobComponent, HourlyWage);
    DOREPLIFETIME(UDaniPlayerJobComponent, CommissionEarned);
}

void UDaniPlayerJobComponent::AddWorkedHours(float Hours)
{
    if (GetOwnerRole() == ROLE_Authority && CurrentJob != EJobType::None)
    {
        WorkedHoursToday += Hours;
    }
}

void UDaniPlayerJobComponent::AddCommission(float Amount)
{
    if (GetOwnerRole() == ROLE_Authority && CurrentJob != EJobType::None)
    {
        CommissionEarned += Amount;
    }
}

void UDaniPlayerJobComponent::PayDailyWages()
{
    if (GetOwnerRole() == ROLE_Authority && CurrentJob != EJobType::None)
    {
        float TotalPayment = (WorkedHoursToday * HourlyWage) + CommissionEarned;

        APJ1* Player = Cast<APJ1>(GetOwner());
        if (Player)
        {
            // Asume que PJ1 tiene un método AddMoney
            Player->AddMoney(TotalPayment);
        }

        // Resetear contadores
        WorkedHoursToday = 0.0f;
        CommissionEarned = 0.0f;
    }
}

bool UDaniPlayerJobComponent::CanHire() const
{
    switch (CurrentJob)
    {
    case EJobType::AdmiralOfTheGuard: return CurrentRank == EJobRank::Admiral;
    case EJobType::NobleHigh: return true; // Nobles altos pueden contratar guardias
    case EJobType::Blacksmith: return CurrentRank == EJobRank::Master;
        // ... otros casos
    default: return false;
    }
}

bool UDaniPlayerJobComponent::CanFire(const UDaniPlayerJobComponent* TargetJobComponent) const
{
    if (!TargetJobComponent) return false;

    // Solo puedes despedir en tu mismo trabajo
    if (CurrentJob != TargetJobComponent->CurrentJob) return false;

    // Verificar jerarquía
    switch (CurrentJob)
    {
    case EJobType::AdmiralOfTheGuard:
        return CurrentRank == EJobRank::Admiral && TargetJobComponent->CurrentRank != CurrentRank;
        // ... otros casos
    default: return CanHire();
    }
}

void UDaniPlayerJobComponent::SetJobAndRank(EJobType NewJob, EJobRank NewRank)
{
    if (GetOwnerRole() == ROLE_Authority)
    {
        CurrentJob = NewJob;
        CurrentRank = NewRank;
        CalculateHourlyWage();
        OnRep_JobData();
    }
}

float UDaniPlayerJobComponent::GetBaseSalary(EJobType Job, EJobRank Rank)
{
    TPair<EJobType, EJobRank> Key(Job, Rank);
    return BaseSalaries.Contains(Key) ? BaseSalaries[Key] : 0.0f;
}

void UDaniPlayerJobComponent::CalculateHourlyWage()
{
    // Base salary / 160 horas (20 días * 8 horas)
    HourlyWage = GetBaseSalary(CurrentJob, CurrentRank) / 160.0f;
}

void UDaniPlayerJobComponent::OnRep_JobData()
{
    // Actualizar UI u otros sistemas cuando cambia el trabajo/rango
    CalculateHourlyWage();
}