#include "DaniFistStyle.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Components/CapsuleComponent.h"

void UDaniFistStyle::ExecuteAttack_Implementation(int32 AttackIndex)
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // Efecto de sonido del movimiento del puño
    if (FistWhooshSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FistWhooshSound, OwnerCharacter->GetActorLocation());
    }

    // Efecto visual del trail del puño
    SpawnFistTrail();

    // Ejecutar combo
    PlayFistCombo(AttackIndex);

    // Aplicar impacto
    ApplyFistImpact();
}

void UDaniFistStyle::StartBlock_Implementation()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // Activar efectos de bloqueo
    OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OwnerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
}

void UDaniFistStyle::EndBlock_Implementation()
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // Desactivar efectos de bloqueo
    OwnerCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    OwnerCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
}

void UDaniFistStyle::PlayFistCombo(int32 ComboIndex)
{
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (!OwnerCharacter) return;

    // Aquí iría la lógica para cargar diferentes montages de animación
    // según el ComboIndex, por ejemplo:
    UAnimMontage* SelectedMontage = nullptr;

    switch (ComboIndex)
    {
    case 0:
        // Cargar montage de combo básico
        break;
    case 1:
        // Cargar montage de combo rápido
        break;
        // ... otros combos
    }

    if (SelectedMontage)
    {
        OwnerCharacter->PlayAnimMontage(SelectedMontage);
    }
}

void UDaniFistStyle::ApplyFistImpact()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    FVector Start = Owner->GetActorLocation();
    FVector ForwardVector = Owner->GetActorForwardVector();
    FVector End = Start + ForwardVector * FistRange;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Pawn,
        Params
    );

    if (bHit && HitResult.GetActor())
    {
        // Aplicar daño
        UGameplayStatics::ApplyDamage(
            HitResult.GetActor(),
            BaseDamage,
            nullptr,
            Owner,
            nullptr
        );

        // Efecto de impacto
        if (FistImpactEffect)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                FistImpactEffect,
                HitResult.ImpactPoint,
                HitResult.ImpactNormal.Rotation()
            );
        }

        // Sonido de impacto
        if (FistImpactSound)
        {
            UGameplayStatics::PlaySoundAtLocation(
                this,
                FistImpactSound,
                HitResult.ImpactPoint
            );
        }

        // Hit stop (congelar frames brevemente)
        TriggerHitStop(0.1f);

        // Sacudida de cámara
        TriggerScreenShake(0.5f);
    }
}

void UDaniFistStyle::SpawnFistTrail()
{
    AActor* Owner = GetOwner();
    if (!Owner || !FistImpactEffect) return;

    // Crear efecto visual del trail del puño
    UParticleSystemComponent* TrailEffect = UGameplayStatics::SpawnEmitterAttached(
        FistImpactEffect,
        Owner->GetRootComponent(),
        NAME_None,
        Owner->GetActorLocation(),
        Owner->GetActorRotation(),
        EAttachLocation::KeepWorldPosition,
        true
    );

    if (TrailEffect)
    {
        TrailEffect->SetWorldScale3D(FVector(0.5f)); // Ajustar tamaño
        TrailEffect->SetRelativeRotation(FRotator(0, 90, 0)); // Orientación correcta
    }
}

void UDaniFistStyle::TriggerScreenShake(float Intensity)
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn) return;

    APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
    if (PC && PC->IsLocalController())
    {
        PC->ClientStartCameraShake(
            UCameraShakeBase::StaticClass(),
            Intensity
        );
    }
}

void UDaniFistStyle::TriggerHitStop(float Duration)
{
    // Implementar lógica de hit stop (congelar el tiempo brevemente)
    // Esto requiere un sistema de gestión de tiempo global
    // que pueda manejar efectos de slow motion/hit stop
}