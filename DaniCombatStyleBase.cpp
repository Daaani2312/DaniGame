#include "DaniCombatStyleBase.h"
#include "PJ1.h" // Tu clase de personaje
#include "DaniStatsComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

UDaniCombatStyleBase::UDaniCombatStyleBase()
{
    PrimaryComponentTick.bCanEverTick = false;
    bInCombatMode = false;
    bIsBlocking = false;
    CombatOwner = nullptr;
    StatsComponent = nullptr;
}

void UDaniCombatStyleBase::BeginPlay()
{
    Super::BeginPlay();

    CombatOwner = GetOwner();
    if (CombatOwner)
    {
        StatsComponent = CombatOwner->FindComponentByClass<UDaniStatsComponent>();
    }
}

void UDaniCombatStyleBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Limpieza al destruirse
    CombatOwner = nullptr;
    StatsComponent = nullptr;
}

void UDaniCombatStyleBase::ActivateStyle(bool bReset)
{
    Super::Activate(bReset);

    // Inicializaci�n del estilo de combate
    if (ACharacter* Character = GetOwnerCharacter())
    {
        // Configurar movimiento para combate
        Character->GetCharacterMovement()->bOrientRotationToMovement = false;
        Character->bUseControllerRotationYaw = true;
    }

    // Efecto visual de activaci�n
    if (CombatStartEffect)
    {
        UGameplayStatics::SpawnEmitterAttached(
            CombatStartEffect,
            GetOwner()->GetRootComponent()
        );
    }
}

void UDaniCombatStyleBase::DeactivateStyle()
{
    // Salir del modo combate si est� activo
    if (bInCombatMode)
    {
        ExitCombatMode();
    }

    // Restaurar movimiento normal
    if (ACharacter* Character = GetOwnerCharacter())
    {
        Character->GetCharacterMovement()->bOrientRotationToMovement = true;
        Character->bUseControllerRotationYaw = false;
    }

    // Efecto visual de desactivaci�n
    if (CombatEndEffect)
    {
        UGameplayStatics::SpawnEmitterAttached(
            CombatEndEffect,
            GetOwner()->GetRootComponent()
        );
    }

    Super::Deactivate();
}

void UDaniCombatStyleBase::EnterCombatMode_Implementation()
{
    if (bInCombatMode || !CombatOwner) return;

    bInCombatMode = true;

    // L�gica com�n para entrar en modo combate
    if (StatsComponent)
    {
        StatsComponent->SetCombatMode(true);
    }
}

void UDaniCombatStyleBase::ExitCombatMode_Implementation()
{
    if (!bInCombatMode) return;

    bInCombatMode = false;
    bIsBlocking = false;

    // L�gica com�n para salir del modo combate
    if (StatsComponent)
    {
        StatsComponent->SetCombatMode(false);
    }
}

void UDaniCombatStyleBase::ExecuteAttack_Implementation(int32 AttackIndex)
{
    if (!CombatOwner || !StatsComponent || StatsComponent->IsExhausted()) return;

    // Reproducir animaci�n de ataque si existe
    if (AttackMontages.Contains(AttackIndex))
    {
        if (ACharacter* Character = GetOwnerCharacter())
        {
            Character->PlayAnimMontage(AttackMontages[AttackIndex]);
        }
    }
}

void UDaniCombatStyleBase::StartBlocking_Implementation()
{
    if (bIsBlocking || !StatsComponent || StatsComponent->IsExhausted()) return;

    bIsBlocking = true;

    // Reproducir animaci�n de bloqueo si existe
    if (BlockStartMontage)
    {
        if (ACharacter* Character = GetOwnerCharacter())
        {
            Character->PlayAnimMontage(BlockStartMontage);
        }
    }

    // Configurar f�sica para bloqueo
    if (ACharacter* Character = GetOwnerCharacter())
    {
        Character->GetCharacterMovement()->MaxWalkSpeed *= 0.5f; // Reducir velocidad al bloquear
    }
}

void UDaniCombatStyleBase::EndBlocking_Implementation()
{
    if (!bIsBlocking) return;

    bIsBlocking = false;

    // Reproducir animaci�n de fin de bloqueo si existe
    if (BlockEndMontage)
    {
        if (ACharacter* Character = GetOwnerCharacter())
        {
            Character->PlayAnimMontage(BlockEndMontage);
        }
    }

    // Restaurar movimiento normal
    if (ACharacter* Character = GetOwnerCharacter())
    {
        Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetCharacterMovement()->GetMaxSpeed();
    }
}

void UDaniCombatStyleBase::ActivateAbility_Implementation(int32 AbilityIndex)
{
    if (!CombatOwner || !StatsComponent || StatsComponent->IsExhausted()) return;

    // L�gica base para activar habilidades
    // Las implementaciones espec�ficas deben sobrescribir esto
}

void UDaniCombatStyleBase::ReloadWeapon_Implementation()
{
    if (!CombatOwner || !StatsComponent || StatsComponent->IsExhausted()) return;

    // L�gica base para recargar armas
    // Las implementaciones espec�ficas deben sobrescribir esto
}

ACharacter* UDaniCombatStyleBase::GetOwnerCharacter() const
{
    return Cast<ACharacter>(CombatOwner);
}