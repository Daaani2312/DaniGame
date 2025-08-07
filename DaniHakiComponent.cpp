#include "DaniEnergyComponent.h"
#include "DaniStatsComponent.h"
#include "DaniCharacter.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

UDaniEnergyComponent::UDaniEnergyComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);

    // Valores por defecto para cada tipo de energía (ajusta a gusto)
    EnergyConfig.Add(EEnergyType::ArmorEnergy, { 10, 0.01f, 5.0f, 0.0f });
    EnergyConfig.Add(EEnergyType::SenseEnergy, { 15, 0.15f, 8.0f, 0.0f });
    EnergyConfig.Add(EEnergyType::WillEnergy, { 20, 0.25f, 30.0f, 30.0f });
}

void UDaniEnergyComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ADaniCharacter>(GetOwner());
    StatsComponent = OwnerCharacter ? OwnerCharacter->FindComponentByClass<UDaniStatsComponent>() : nullptr;

    for (EEnergyType Energy : TEnumRange<EEnergyType>())
    {
        if (Energy == EEenergyType::MAX) continue;
        EnergyUsageCounts.Add(Energy, 0);
        EnergyLevels.Add(Energy, 1);
        ActiveEnergies.Add(Energy, false);
        EnergyCooldowns.Add(Energy, 0.0f);
    }
}

bool UDaniEnergyComponent::TryActivateEnergy(EEnergyType EnergyType)
{
    if (!OwnerCharacter || !StatsComponent || bIsParalyzed) return false;
    if (ActiveEnergies[EnergyType]) return false;

    const float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime < EnergyCooldowns[EnergyType])
        return false;

    const float StaminaCost = GetStaminaCostForEnergy(EnergyType);
    if (!StatsComponent->TryConsumeStamina(StaminaCost))
        return false;

    ActiveEnergies[EnergyType] = true;
    IncreaseEnergyUsage(EnergyType);
    ApplyEnergyEffects(EnergyType, true);

    // Timers según tipo de energía
    switch (EnergyType)
    {
    case EEnergyType::SenseEnergy:
        GetWorld()->GetTimerManager().SetTimer(
            SenseEnergyTickHandle,
            this,
            &UDaniEnergyComponent::OnSenseEnergyTick,
            EnergyConfig[EnergyType].ActiveDuration,
            true
        );
        break;

    case EEnergyType::WillEnergy:
        GetWorld()->GetTimerManager().SetTimer(
            WillEnergyTimerHandle,
            this,
            &UDaniEnergyComponent::DeactivateEnergy,
            EnergyConfig[EnergyType].ActiveDuration,
            false
        );
        HandleSenseEnergyDetection();
        break;

    case EEnergyType::ArmorEnergy:
        // Defensa permanente, sin timer
        break;
    }

    OnEnergyActivated.Broadcast(EnergyType, StaminaCost);
    return true;
}

void UDaniEnergyComponent::DeactivateEnergy(EEnergyType EnergyType)
{
    if (!ActiveEnergies[EnergyType]) return;

    ActiveEnergies[EnergyType] = false;
    EnergyCooldowns[EnergyType] = GetWorld()->GetTimeSeconds() + EnergyConfig[EnergyType].CooldownDuration;
    ApplyEnergyEffects(EnergyType, false);

    // Limpieza de timers
    switch (EnergyType)
    {
    case EEnergyType::SenseEnergy:
        GetWorld()->GetTimerManager().ClearTimer(SenseEnergyTickHandle);
        break;

    case EEnergyType::WillEnergy:
        GetWorld()->GetTimerManager().ClearTimer(WillEnergyTimerHandle);
        break;

    case EEnergyType::ArmorEnergy:
        // Nada especial aquí
        break;
    }

    OnEnergyDeactivated.Broadcast(EnergyType);
}

void UDaniEnergyComponent::OnSenseEnergyTick()
{
    if (!StatsComponent || !ActiveEnergies[EEnergyType::SenseEnergy])
    {
        GetWorld()->GetTimerManager().ClearTimer(SenseEnergyTickHandle);
        return;
    }

    const float CostPerTick = GetStaminaCostForEnergy(EEnergyType::SenseEnergy) * 0.1f;
    if (!StatsComponent->TryConsumeStamina(CostPerTick))
    {
        DeactivateEnergy(EEnergyType::SenseEnergy);
    }
}

void UDaniEnergyComponent::IncreaseEnergyUsage(EEnergyType EnergyType)
{
    if (!EnergyUsageCounts.Contains(EnergyType)) return;

    EnergyUsageCounts[EnergyType]++;
    CheckLevelUp(EnergyType);
}

void UDaniEnergyComponent::CheckLevelUp(EEnergyType EnergyType)
{
    int32& Usage = EnergyUsageCounts[EnergyType];
    int32& Level = EnergyLevels[EnergyType];
    const int32 XPNeeded = EnergyConfig[EnergyType].XPToNextLevel * Level;

    if (Usage >= XPNeeded)
    {
        Level++;
        Usage -= XPNeeded;
        OnEnergyLevelUp.Broadcast(EnergyType, Level);
    }
}

float UDaniEnergyComponent::GetStaminaCostForEnergy(EEnergyType EnergyType) const
{
    if (!StatsComponent || !EnergyConfig.Contains(EnergyType)) return 0.0f;

    const float BaseStamina = StatsComponent->GetBaseStats().MaxStamina;
    const int32 Level = EnergyLevels[EnergyType];
    float Cost = EnergyConfig[EnergyType].BaseStaminaCost * BaseStamina;

    switch (EnergyType)
    {
    case EEnergyType::ArmorEnergy:
        return (Level >= 2) ? 0.0f : Cost;

    case EEnergyType::SenseEnergy:
        if (Level >= 3) return Cost * 0.33f;
        if (Level == 2) return Cost * 0.66f;
        return Cost;

    case EEnergyType::WillEnergy:
        return Cost;
    }

    return Cost;
}

float UDaniEnergyComponent::GetStatMultiplierForEnergy(EEnergyType EnergyType) const
{
    const int32 Level = EnergyLevels[EnergyType];

    switch (EnergyType)
    {
    case EEnergyType::ArmorEnergy:
        return 1.0f + (0.15f * Level);

    case EEnergyType::SenseEnergy:
        return 1.0f + (0.1f * Level);

    case EEnergyType::WillEnergy:
        return 1.0f + (0.2f * Level);
    }

    return 1.0f;
}

void UDaniEnergyComponent::ApplyEnergyEffects(EEnergyType EnergyType, bool bActivate)
{
    if (!StatsComponent) return;

    const float Multiplier = bActivate ? GetStatMultiplierForEnergy(EnergyType) : 1.0f;

    switch (EnergyType)
    {
    case EEnergyType::ArmorEnergy:
        StatsComponent->SetDefenseModifier(bActivate ? 0.5f * Multiplier : -0.5f);
        break;

    case EEnergyType::SenseEnergy:
        StatsComponent->SetDodgeChanceModifier(bActivate ? 0.3f * Multiplier : -0.3f);
        break;

    case EEnergyType::WillEnergy:
        StatsComponent->SetAttackModifier(bActivate ? 0.4f * Multiplier : -0.4f);
        break;
    }
}

void UDaniEnergyComponent::HandleSenseEnergyDetection()
{
    if (!ActiveEnergies[EEnergyType::SenseEnergy]) return;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADaniCharacter::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (Actor != GetOwner())
        {
            // Aquí va la lógica para detectar enemigos con SenseEnergy
            // Puedes poner un outline, icono, o alertar al jugador
        }
    }
}

void UDaniEnergyComponent::ApplyParalysis(float Duration)
{
    if (bIsParalyzed) return;

    bIsParalyzed = true;
    OnParalysisStateChanged.Broadcast(true);

    // Desactivar todas las energías activas
    for (auto& Energy : ActiveEnergies)
    {
        if (Energy.Value)
        {
            DeactivateEnergy(Energy.Key);
        }
    }

    if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
    {
        OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed *= ParalysisMoveSpeedReduction;
    }

    GetWorld()->GetTimerManager().SetTimer(
        ParalysisTimerHandle,
        this,
        &UDaniEnergyComponent::EndParalysis,
        Duration,
        false
    );
}

void UDaniEnergyComponent::EndParalysis()
{
    bIsParalyzed = false;

    if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
    {
        OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed /= ParalysisMoveSpeedReduction;
    }

    OnParalysisStateChanged.Broadcast(false);
}

void UDaniEnergyComponent::ClearParalysis()
{
    bIsParalyzed = false;
    GetWorld()->GetTimerManager().ClearTimer(ParalysisTimerHandle);

    if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
    {
        OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed /= ParalysisMoveSpeedReduction;
    }

    OnParalysisStateChanged.Broadcast(false);
}

void UDaniEnergyComponent::HandleEnergyClash(UDaniEnergyComponent* OtherEnergyComponent)
{
    if (!OtherEnergyComponent || !ActiveEnergies[EEnergyType::WillEnergy] ||
        !OtherEnergyComponent->IsEnergyActive(EEnergyType::WillEnergy))
    {
        return;
    }

    const int32 MyLevel = EnergyLevels[EEnergyType::WillEnergy];
    const int32 OtherLevel = OtherEnergyComponent->EnergyLevels[EEnergyType::WillEnergy];

    if (MyLevel > OtherLevel)
    {
        OtherEnergyComponent->ApplyParalysis(5.0f * (MyLevel - OtherLevel));
    }
    else if (OtherLevel > MyLevel)
    {
        ApplyParalysis(5.0f * (OtherLevel - MyLevel));
    }
    else
    {
        ApplyParalysis(2.5f);
        OtherEnergyComponent->ApplyParalysis(2.5f);
    }
}

void UDaniEnergyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (ActiveEnergies[EEnergyType::SenseEnergy])
    {
        HandleSenseEnergyDetection();
    }
}

void UDaniEnergyComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UDaniEnergyComponent, EnergyUsageCounts);
    DOREPLIFETIME(UDaniEnergyComponent, EnergyLevels);
    DOREPLIFETIME(UDaniEnergyComponent, ActiveEnergies);
    DOREPLIFETIME(UDaniEnergyComponent, EnergyCooldowns);
    DOREPLIFETIME(UDaniEnergyComponent, bIsParalyzed);
}
