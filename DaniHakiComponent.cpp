#include "DaniHakiComponent.h"
#include "PJ1.h"
#include "DaniStatsComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

UDaniHakiComponent::UDaniHakiComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // Inicializar datos de nivel
    TArray<FHakiLevelData> ArmamentLevels;
    ArmamentLevels.Add({ 0, 0.2f, 0.3f, 0.0f, 0.0f, 0.0f, 5.0f, 10.0f }); // Nivel 1
    ArmamentLevels.Add({ 100, 0.3f, 0.5f, 0.0f, 0.0f, 0.0f, 7.0f, 15.0f }); // Nivel 2
    ArmamentLevels.Add({ 250, 0.5f, 0.7f, 0.0f, 0.0f, 0.0f, 10.0f, 20.0f }); // Nivel 3
    HakiLevelData.Add(EHakiType::Armament, ArmamentLevels);

    TArray<FHakiLevelData> ObservationLevels;
    ObservationLevels.Add({ 0, 0.0f, 0.0f, 0.2f, 0.0f, 0.0f, 4.0f, 12.0f }); // Nivel 1
    ObservationLevels.Add({ 100, 0.0f, 0.0f, 0.3f, 0.3f, 0.5f, 6.0f, 18.0f }); // Nivel 2
    ObservationLevels.Add({ 250, 0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 8.0f, 25.0f }); // Nivel 3
    HakiLevelData.Add(EHakiType::Observation, ObservationLevels);

    TArray<FHakiLevelData> ConquerorsLevels;
    ConquerorsLevels.Add({ 0, 0.3f, 0.1f, 0.1f, 0.0f, 0.0f, 8.0f, 8.0f }); // Nivel 1
    ConquerorsLevels.Add({ 100, 0.5f, 0.2f, 0.2f, 0.0f, 0.0f, 12.0f, 12.0f }); // Nivel 2
    ConquerorsLevels.Add({ 250, 0.8f, 0.3f, 0.3f, 0.0f, 0.0f, 15.0f, 15.0f }); // Nivel 3
    HakiLevelData.Add(EHakiType::Conquerors, ConquerorsLevels);

    // Inicializar progreso
    for (int32 i = 0; i < static_cast<int32>(EHakiType::MAX); ++i)
    {
        EHakiType Type = static_cast<EHakiType>(i);
        HakiProgressMap.Add(Type, FHakiProgress());
        ActiveHakiTypes.Add(Type, false);
    }
}

void UDaniHakiComponent::BeginPlay()
{
    Super::BeginPlay();

    // Desbloquear nivel 1 inicial
    for (auto& Elem : HakiProgressMap)
    {
        Elem.Value.bIsUnlocked = true;
    }
}

void UDaniHakiComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Consumir stamina por Haki activo
    for (const auto& Elem : ActiveHakiTypes)
    {
        if (Elem.Value)
        {
            ConsumeHakiStamina(Elem.Key);
        }
    }
}

void UDaniHakiComponent::ToggleHaki(EHakiType HakiType)
{
    if (ActiveHakiTypes[HakiType])
    {
        DeactivateHaki(HakiType);
    }
    else
    {
        ActivateHaki(HakiType);
    }
}

void UDaniHakiComponent::ActivateHaki(EHakiType HakiType)
{
    if (ActiveHakiTypes[HakiType] || !HakiProgressMap[HakiType].bIsUnlocked)
        return;

    APJ1* OwnerCharacter = Cast<APJ1>(GetOwner());
    if (!OwnerCharacter || !OwnerCharacter->StatsComponent)
        return;

    // Verificar stamina suficiente
    const FHakiLevelData& LevelData = HakiLevelData[HakiType][static_cast<int32>(HakiProgressMap[HakiType].CurrentLevel)];
    if (!OwnerCharacter->StatsComponent->HasEnoughStamina(LevelData.StaminaCostPerSecond))
        return;

    ActiveHakiTypes[HakiType] = true;
    ApplyHakiEffects(HakiType, true);
    OnHakiActivated.Broadcast(HakiType, true);

    // Configurar temporizador de duración
    if (LevelData.BaseDuration > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(
            HakiTimerHandles[HakiType],
            this,
            &UDaniHakiComponent::OnHakiDurationExpired,
            LevelData.BaseDuration,
            false,
            HakiType
        );
    }
}

void UDaniHakiComponent::DeactivateHaki(EHakiType HakiType)
{
    if (!ActiveHakiTypes[HakiType])
        return;

    ActiveHakiTypes[HakiType] = false;
    ApplyHakiEffects(HakiType, false);
    OnHakiActivated.Broadcast(HakiType, false);

    // Limpiar temporizador
    if (HakiTimerHandles.Contains(HakiType) && HakiTimerHandles[HakiType].IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(HakiTimerHandles[HakiType]);
    }
}

void UDaniHakiComponent::AddHakiXP(EHakiType HakiType, int32 XPAmount)
{
    if (!HakiProgressMap.Contains(HakiType) || HakiProgressMap[HakiType].CurrentLevel == EHakiLevel::Level3)
        return;

    FHakiProgress& Progress = HakiProgressMap[HakiType];
    Progress.CurrentXP += XPAmount;
    CheckForLevelUp(HakiType);
}

EHakiLevel UDaniHakiComponent::GetHakiLevel(EHakiType HakiType) const
{
    return HakiProgressMap.Contains(HakiType) ? HakiProgressMap[HakiType].CurrentLevel : EHakiLevel::Level1;
}

bool UDaniHakiComponent::IsHakiActive(EHakiType HakiType) const
{
    return ActiveHakiTypes.Contains(HakiType) && ActiveHakiTypes[HakiType];
}

float UDaniHakiComponent::GetRecoilReduction() const
{
    if (!IsHakiActive(EHakiType::Observation) || GetHakiLevel(EHakiType::Observation) < EHakiLevel::Level2)
        return 0.0f;

    return HakiLevelData[EHakiType::Observation][static_cast<int32>(GetHakiLevel(EHakiType::Observation))].RecoilReduction;
}

float UDaniHakiComponent::GetAimAssistStrength() const
{
    if (!IsHakiActive(EHakiType::Observation) || GetHakiLevel(EHakiType::Observation) < EHakiLevel::Level3)
        return 0.0f;

    return HakiLevelData[EHakiType::Observation][static_cast<int32>(GetHakiLevel(EHakiType::Observation))].AimAssistStrength;
}

void UDaniHakiComponent::ApplyHakiEffects(EHakiType HakiType, bool bActivate)
{
    APJ1* OwnerCharacter = Cast<APJ1>(GetOwner());
    if (!OwnerCharacter || !OwnerCharacter->StatsComponent)
        return;

    const EHakiLevel CurrentLevel = HakiProgressMap[HakiType].CurrentLevel;
    const FHakiLevelData& LevelData = HakiLevelData[HakiType][static_cast<int32>(CurrentLevel)];

    if (bActivate)
    {
        // Aplicar buffs
        OwnerCharacter->StatsComponent->AddAttackModifier(LevelData.AttackModifier);
        OwnerCharacter->StatsComponent->AddDefenseModifier(LevelData.DefenseModifier);
        OwnerCharacter->StatsComponent->AddDodgeModifier(LevelData.DodgeModifier);

        // Efectos visuales
        // (Implementar según necesidades)
    }
    else
    {
        // Remover buffs
        OwnerCharacter->StatsComponent->AddAttackModifier(-LevelData.AttackModifier);
        OwnerCharacter->StatsComponent->AddDefenseModifier(-LevelData.DefenseModifier);
        OwnerCharacter->StatsComponent->AddDodgeModifier(-LevelData.DodgeModifier);

        // Limpiar efectos visuales
    }
}

void UDaniHakiComponent::CheckForLevelUp(EHakiType HakiType)
{
    FHakiProgress& Progress = HakiProgressMap[HakiType];
    if (Progress.CurrentLevel == EHakiLevel::Level3)
        return;

    int32 NextLevelXP = HakiLevelData[HakiType][static_cast<int32>(Progress.CurrentLevel) + 1].XPRequired;
    if (Progress.CurrentXP >= NextLevelXP)
    {
        Progress.CurrentLevel = static_cast<EHakiLevel>(static_cast<int32>(Progress.CurrentLevel) + 1);
        OnHakiLevelChanged.Broadcast(HakiType, true);

        // Desbloquear habilidades especiales al alcanzar ciertos niveles
        if (Progress.CurrentLevel == EHakiLevel::Level2 || Progress.CurrentLevel == EHakiLevel::Level3)
        {
            // Notificar al jugador de nuevas habilidades desbloqueadas
        }
    }
}

void UDaniHakiComponent::OnHakiDurationExpired(EHakiType HakiType)
{
    DeactivateHaki(HakiType);
}

void UDaniHakiComponent::ConsumeHakiStamina(EHakiType HakiType)
{
    APJ1* OwnerCharacter = Cast<APJ1>(GetOwner());
    if (!OwnerCharacter || !OwnerCharacter->StatsComponent)
        return;

    const FHakiLevelData& LevelData = HakiLevelData[HakiType][static_cast<int32>(HakiProgressMap[HakiType].CurrentLevel)];
    if (!OwnerCharacter->StatsComponent->ConsumeStamina(LevelData.StaminaCostPerSecond * GetWorld()->GetDeltaSeconds()))
    {
        // No hay suficiente stamina, desactivar Haki
        DeactivateHaki(HakiType);
    }
}