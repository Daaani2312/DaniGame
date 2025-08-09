#include "DaniSwordStyle.h"
#include "DaniSwordWeapon.h"
#include "PJ1.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

UDaniSwordStyle::UDaniSwordStyle()
{
    CurrentStyle = ESwordStyleType::SingleKatana;
    EquippedSword = nullptr;
    ActiveStyleEffect = nullptr;
}

void UDaniSwordStyle::OnActivated_Implementation(AActor* OwnerActor)
{
    Super::OnActivated_Implementation(OwnerActor);

    // Configurar estilo inicial
    ChangeSwordStyle(CurrentStyle);
}

void UDaniSwordStyle::OnDeactivated_Implementation()
{
    // Limpiar efectos y arma
    if (ActiveStyleEffect)
    {
        ActiveStyleEffect->DestroyComponent();
        ActiveStyleEffect = nullptr;
    }

    if (EquippedSword)
    {
        EquippedSword->Destroy();
        EquippedSword = nullptr;
    }

    Super::OnDeactivated_Implementation();
}

void UDaniSwordStyle::ChangeSwordStyle(ESwordStyleType NewStyle)
{
    if (CurrentStyle == NewStyle) return;

    CurrentStyle = NewStyle;

    // Configurar el nuevo estilo
    SetupWeaponForStyle();
    SetupStyleEffects();
}

void UDaniSwordStyle::ExecuteAttack_Implementation(int32 AttackIndex)
{
    if (!GetOwner() || !EquippedSword) return;

    // Obtener variante de estilo actual
    const FSwordStyleVariant* CurrentVariant = GetCurrentStyleVariant();
    if (!CurrentVariant || !CurrentVariant->AttackAnimations.IsValidIndex(AttackIndex)) return;

    // Reproducir animación de ataque
    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        Character->PlayAnimMontage(CurrentVariant->AttackAnimations[AttackIndex]);
    }

    // Configurar golpe de espada
    CheckSwordHit();
}

void UDaniSwordStyle::StartBlock_Implementation()
{
    const FSwordStyleVariant* CurrentVariant = GetCurrentStyleVariant();
    if (!CurrentVariant || !CurrentVariant->BlockAnimation) return;

    if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
    {
        Character->PlayAnimMontage(CurrentVariant->BlockAnimation);
    }

    Super::StartBlock_Implementation();
}

void UDaniSwordStyle::EndBlock_Implementation()
{
    Super::EndBlock_Implementation();
}

const FSwordStyleVariant* UDaniSwordStyle::GetCurrentStyleVariant() const
{
    for (const FSwordStyleVariant& Variant : StyleVariants)
    {
        if (Variant.StyleType == CurrentStyle)
        {
            return &Variant;
        }
    }
    return nullptr;
}

void UDaniSwordStyle::SetupStyleEffects()
{
    // Limpiar efecto anterior
    if (ActiveStyleEffect)
    {
        ActiveStyleEffect->DestroyComponent();
        ActiveStyleEffect = nullptr;
    }

    // Configurar nuevo efecto
    const FSwordStyleVariant* CurrentVariant = GetCurrentStyleVariant();
    if (CurrentVariant && CurrentVariant->StyleEffect)
    {
        ActiveStyleEffect = UGameplayStatics::SpawnEmitterAttached(
            CurrentVariant->StyleEffect,
            GetOwner()->GetRootComponent()
        );
    }
}

void UDaniSwordStyle::SetupWeaponForStyle()
{
    // Destruir arma anterior si existe
    if (EquippedSword)
    {
        EquippedSword->Destroy();
        EquippedSword = nullptr;
    }

    // Crear nueva arma según el estilo
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    SpawnParams.Instigator = Cast<APawn>(GetOwner());

    // Determinar qué clase de arma spawnear basado en el estilo
    TSubclassOf<ADaniSwordWeapon> SwordClassToSpawn;

    switch (CurrentStyle)
    {
    case ESwordStyleType::SingleKatana:
        SwordClassToSpawn = SingleKatanaClass;
        break;
    case ESwordStyleType::DualKatanas:
        SwordClassToSpawn = DualKatanasClass;
        break;
        // ... otros casos
    default:
        SwordClassToSpawn = SingleKatanaClass;
    }

    if (SwordClassToSpawn)
    {
        EquippedSword = GetWorld()->SpawnActor<ADaniSwordWeapon>(
            SwordClassToSpawn,
            FTransform::Identity,
            SpawnParams
        );

        if (EquippedSword)
        {
            EquippedSword->AttachToComponent(
                Cast<ACharacter>(GetOwner())->GetMesh(),
                FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                "WeaponSocket" // Nombre del socket donde se une el arma
            );
        }
    }
}

void UDaniSwordStyle::CheckSwordHit()
{
    if (!EquippedSword) return;

    // Lógica de verificación de golpe
    // (Implementar sistema de detección de colisiones basado en el estilo actual)
}