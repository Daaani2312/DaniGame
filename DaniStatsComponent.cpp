#include "DaniStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

UDaniStatsComponent::UDaniStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
}

void UDaniStatsComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = BaseStats.MaxHealth;
    CurrentStamina = BaseStats.MaxStamina;

    WalkSpeedModifier = 1.0f;
    SprintSpeedModifier = 1.0f;

    UpdateMovementSpeed();
}

void UDaniStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UDaniStatsComponent, BaseStats);
    DOREPLIFETIME(UDaniStatsComponent, CurrentHealth);
    DOREPLIFETIME(UDaniStatsComponent, CurrentStamina);
    DOREPLIFETIME(UDaniStatsComponent, bIsExhausted);
}

void UDaniStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bCanRegenStamina && !bIsExhausted)
    {
        RegenerateStamina(DeltaTime);
    }
}

void UDaniStatsComponent::ApplyDamage(float DamageAmount)
{
    if (DamageAmount <= 0.0f) return;

    CurrentHealth = FMath::Max(CurrentHealth - DamageAmount, 0.0f);
    OnStatChanged.Broadcast(EStatType::Health, CurrentHealth);

    if (CurrentHealth <= 0.0f)
    {
        OnHealthDepleted.Broadcast();
    }
}

void UDaniStatsComponent::Heal(float HealAmount)
{
    if (HealAmount <= 0.0f) return;

    CurrentHealth = FMath::Min(CurrentHealth + HealAmount, BaseStats.MaxHealth);
    OnStatChanged.Broadcast(EStatType::Health, CurrentHealth);
}

bool UDaniStatsComponent::TryConsumeStamina(float Amount)
{
    if (CurrentStamina < Amount)
    {
        if (!bIsExhausted)
        {
            HandleStaminaExhaustion();
        }
        return false;
    }

    CurrentStamina -= Amount;
    bCanRegenStamina = false;
    OnStatChanged.Broadcast(EStatType::Stamina, CurrentStamina);

    StartStaminaRegenDelay();

    if (CurrentStamina <= 0.0f && !bIsExhausted)
    {
        HandleStaminaExhaustion();
    }

    return true;
}

void UDaniStatsComponent::StartStaminaRegenDelay(float Delay)
{
    GetWorld()->GetTimerManager().SetTimer(
        StaminaRegenDelayHandle,
        this,
        &UDaniStatsComponent::OnRegenDelayEnded,
        Delay,
        false
    );
}

void UDaniStatsComponent::RegenerateStamina(float DeltaTime)
{
    if (!bCanRegenStamina || CurrentStamina >= BaseStats.MaxStamina)
    {
        return;
    }

    const float RegenAmount = BaseStats.StaminaRegen * DeltaTime;
    CurrentStamina = FMath::Min(CurrentStamina + RegenAmount, BaseStats.MaxStamina);
    OnStatChanged.Broadcast(EStatType::Stamina, CurrentStamina);

    if (bIsExhausted && CurrentStamina >= BaseStats.MaxStamina * 0.3f)
    {
        RecoverFromExhaustion();
    }
}

void UDaniStatsComponent::OnRegenDelayEnded()
{
    bCanRegenStamina = true;
}

void UDaniStatsComponent::HandleStaminaExhaustion()
{
    if (bIsExhausted) return;

    bIsExhausted = true;
    OnStaminaExhausted.Broadcast();

    AddWalkSpeedModifier(-0.5f);
    AddSprintSpeedModifier(-0.7f);
    UpdateMovementSpeed();

    GetWorld()->GetTimerManager().SetTimer(
        ExhaustionRecoveryHandle,
        this,
        &UDaniStatsComponent::RecoverFromExhaustion,
        5.0f,
        false
    );
}

void UDaniStatsComponent::RecoverFromExhaustion()
{
    if (!bIsExhausted) return;

    bIsExhausted = false;

    AddWalkSpeedModifier(0.5f);
    AddSprintSpeedModifier(0.7f);
    UpdateMovementSpeed();
}

// --- Los métodos AddDefenseModifier, AddAttackModifier, etc., y getters quedan igual ---

void UDaniStatsComponent::AddDefenseModifier(float Modifier)
{
    DefenseModifier += Modifier;
    OnStatChanged.Broadcast(EStatType::Defense, GetCurrentDefense());
}

void UDaniStatsComponent::AddAttackModifier(float Modifier)
{
    AttackModifier += Modifier;
    OnStatChanged.Broadcast(EStatType::Attack, GetCurrentAttack());
}

void UDaniStatsComponent::AddDodgeChanceModifier(float Modifier)
{
    DodgeChanceModifier += Modifier;
    OnStatChanged.Broadcast(EStatType::DodgeChance, GetCurrentDodgeChance());
}

void UDaniStatsComponent::AddWalkSpeedModifier(float Modifier)
{
    WalkSpeedModifier = FMath::Max(WalkSpeedModifier + Modifier, 0.1f);
    UpdateMovementSpeed();
    OnStatChanged.Broadcast(EStatType::WalkSpeed, GetCurrentWalkSpeed());
}

void UDaniStatsComponent::AddSprintSpeedModifier(float Modifier)
{
    SprintSpeedModifier = FMath::Max(SprintSpeedModifier + Modifier, 0.1f);
    UpdateMovementSpeed();
    OnStatChanged.Broadcast(EStatType::SprintSpeed, GetCurrentSprintSpeed());
}

void UDaniStatsComponent::UpdateMovementSpeed()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter && OwnerCharacter->GetCharacterMovement())
    {
        OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GetCurrentWalkSpeed();
        // SprintSpeed se maneja en otro lugar al iniciar sprint
    }
}

float UDaniStatsComponent::GetCurrentDefense() const
{
    return BaseStats.Defense * (1.0f + DefenseModifier);
}

float UDaniStatsComponent::GetCurrentAttack() const
{
    return BaseStats.AttackPower * (1.0f + AttackModifier);
}

float UDaniStatsComponent::GetCurrentDodgeChance() const
{
    return FMath::Clamp(BaseStats.DodgeChance * (1.0f + DodgeChanceModifier), 0.0f, 0.95f);
}

float UDaniStatsComponent::GetCurrentWalkSpeed() const
{
    return BaseStats.WalkSpeed * WalkSpeedModifier;
}

float UDaniStatsComponent::GetCurrentSprintSpeed() const
{
    return BaseStats.SprintSpeed * SprintSpeedModifier;
}

float UDaniStatsComponent::GetHealthPercentage() const
{
    return BaseStats.MaxHealth > 0 ? CurrentHealth / BaseStats.MaxHealth : 0.0f;
}

float UDaniStatsComponent::GetStaminaPercentage() const
{
    return BaseStats.MaxStamina > 0 ? CurrentStamina / BaseStats.MaxStamina : 0.0f;
}

bool UDaniStatsComponent::IsExhausted() const
{
    return bIsExhausted;
}
