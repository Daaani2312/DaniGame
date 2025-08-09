#include "PJ1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"

// Componentes existentes
#include "DaniStatsComponent.h"
#include "DaniHakiComponent.h"
#include "DaniCombatComponent.h"
#include "DaniSwordStyle.h"
#include "DaniFistStyle.h"

// NUEVO: Sistema de trabajos y economía
#include "DaniPlayerJobComponent.h"
#include "DaniMarketComponent.h"
#include "DaniRancherComponent.h"

APJ1::APJ1()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bReplicateMovement = true;

    // Componentes existentes
    StatsComponent = CreateDefaultSubobject<UDaniStatsComponent>(TEXT("StatsComponent"));
    HakiComponent = CreateDefaultSubobject<UDaniHakiComponent>(TEXT("HakiComponent"));
    CombatComponent = CreateDefaultSubobject<UDaniCombatComponent>(TEXT("CombatComponent"));

    // NUEVOS COMPONENTES
    JobComponent = CreateDefaultSubobject<UDaniPlayerJobComponent>(TEXT("JobComponent"));
    MarketComponent = CreateDefaultSubobject<UDaniMarketComponent>(TEXT("MarketComponent"));
    RancherComponent = CreateDefaultSubobject<UDaniRancherComponent>(TEXT("RancherComponent"));
}

void APJ1::BeginPlay()
{
    Super::BeginPlay();

    if (CombatComponent)
    {
        CombatComponent->OnCombatModeEnabled.AddDynamic(this, &APJ1::HandleCombatModeEnabled);
        CombatComponent->OnCombatModeDisabled.AddDynamic(this, &APJ1::HandleCombatModeDisabled);
        CombatComponent->OnCombatStyleChanged.AddDynamic(this, &APJ1::HandleCombatStyleChanged);

        // Estilo inicial
        CombatComponent->SwitchCombatStyle(UDaniFistStyle::StaticClass());
    }

    // Aquí podrías iniciar funcionalidades de JobComponent, MarketComponent y RancherComponent si tienen eventos o lógica.
}

void APJ1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    SetupMovementInput();
    SetupHakiInput();
    SetupCombatInput();
}

// -- Las funciones SetupMovementInput, SetupHakiInput, SetupCombatInput y demás acciones de combate van igual que antes --

bool APJ1::CanExecuteCombatAction() const
{
    return CombatComponent &&
        CombatComponent->IsInCombatMode() &&
        StatsComponent &&
        !StatsComponent->IsExhausted();
}

// Resto de funciones para combate (ToggleCombatMode, ExecuteBasicAttack, etc.) igual que las que ya tienes

void APJ1::HandleCombatModeEnabled()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Modo Combate Activado"));
    }
}

void APJ1::HandleCombatModeDisabled()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Modo Combate Desactivado"));
    }
}

void APJ1::HandleCombatStyleChanged(TSubclassOf<UDaniCombatStyleBase> OldStyle, TSubclassOf<UDaniCombatStyleBase> NewStyle)
{
    FString StyleName = NewStyle ? NewStyle->GetName() : "None";
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow,
            FString::Printf(TEXT("Estilo cambiado a: %s"), *StyleName));
    }
}
