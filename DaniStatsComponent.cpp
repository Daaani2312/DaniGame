#include "DaniStatsComponent.h"
#include "PJ1.h"
#include "TimerManager.h"

UDaniStatsComponent::UDaniStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentHealth = 100.0f;
    CurrentStamina = 100.0f;
}

void UDaniStatsComponent::BeginPlay()
{
    Super::BeginPlay();

    // Inicializar stats
    CurrentStats = BaseStats;
    CurrentHealth = BaseStats.MaxHealth;
    CurrentStamina = BaseStats.MaxStamina;

    // Configurar regeneración
    GetWorld()->GetTimerManager().SetTimer(
        RegenerationTimerHandle,
        this,
        &UDaniStatsComponent::RegenerateStamina,
        0.2f, // Intervalo corto para regeneración suave
        true
    );
}

void UDaniStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Actualizar stats modificadas
    UpdateStats();

    // Regeneración continua
    RegenerateStamina(DeltaTime);
}

void UDaniStatsComponent::UpdateStats()
{
    // Copiar stats base
    CurrentStats = BaseStats;

    // Aplicar modificadores de nivel de espada
    float SwordBonus = SwordLevel * 0.05f; // 5% por nivel
    CurrentStats.MeleeDamage *= (1.0f + SwordBonus);

    // Aplicar modificadores de nivel de armas de fuego
    float GunBonus = GunLevel * 0.03f; // 3% por nivel
    CurrentStats.RangedDamage *= (1.0f + GunBonus);
    CurrentStats.RangedAccuracy += GunLevel * 0.02f; // +2% precisión por nivel

    // Aplicar modificadores de Devil Essence
    float EssenceBonus = DevilEssenceLevel * 0.04f; // 4% por nivel
    CurrentStats.SpecialDamage *= (1.0f + EssenceBonus);

    // Aplicar modificadores acumulativos
    CurrentStats.AttackPower *= (1.0f + TotalAttackModifier);
    CurrentStats.DefensePower *= (1.0f + TotalDefenseModifier);
    CurrentStats.DodgeChance = FMath::Clamp(CurrentStats.DodgeChance + TotalDodgeModifier, 0.0f, 0.95f);

    // Notificar cambios
    OnCombatStatChanged.Broadcast(CurrentStats);
}

void UDaniStatsComponent::RegenerateStamina(float DeltaTime)
{
    if (CurrentStamina < CurrentStats.MaxStamina)
    {
        float RegenAmount = CurrentStats.StaminaRegenRate * DeltaTime;
        CurrentStamina = FMath::Min(CurrentStamina + RegenAmount, CurrentStats.MaxStamina);
        OnStatChanged.Broadcast(EStatType::Stamina, CurrentStamina);
    }
}

bool UDaniStatsComponent::ConsumeStamina(float Amount)
{
    if (CurrentStamina >= Amount)
    {
        CurrentStamina -= Amount;
        OnStatChanged.Broadcast(EStatType::Stamina, CurrentStamina);
        return true;
    }
    return false;
}

bool UDaniStatsComponent::HasEnoughStamina(float RequiredStamina) const
{
    return CurrentStamina >= RequiredStamina;
}

void UDaniStatsComponent::AddAttackModifier(float Modifier)
{
    TotalAttackModifier += Modifier;
    UpdateStats();
}

void UDaniStatsComponent::AddDefenseModifier(float Modifier)
{
    TotalDefenseModifier += Modifier;
    UpdateStats();
}

void UDaniStatsComponent::AddDodgeModifier(float Modifier)
{
    TotalDodgeModifier += Modifier;
    UpdateStats();
}