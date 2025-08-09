#include "DaniGameController.h"
#include "PJ1.h"
#include "GameFramework/CheatManager.h"

ADaniGameController::ADaniGameController()
{
    CheatClass = UCheatManager::StaticClass();
}

void ADaniGameController::BeginPlay()
{
    Super::BeginPlay();
}

void ADaniGameController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

ADaniCharacter* ADaniGameController::GetDaniCharacter() const
{
    return Cast<ADaniCharacter>(GetPawn());
}

void ADaniGameController::ValidateAdminPrivileges() const
{
    // Implementar lógica de verificación de admin
}

// ─── ADMIN COMMANDS ────────────────────────────────────────────────
void ADaniGameController::AdminSetConquerorWill(bool bEnable)
{
    if (ADaniCharacter* Character = GetDaniCharacter())
    {
        Character->GetSocialComponent()->SetConquerorWill(bEnable);
    }
}

void ADaniGameController::AdminSetFamily(const FString& FamilyName)
{
    if (ADaniCharacter* Character = GetDaniCharacter())
    {
        Character->GetSocialComponent()->InitializeFamily(FName(*FamilyName));
    }
}

void ADaniGameController::AdminSetRace(const FString& RaceName, bool bIsSamurai)
{
    if (ADaniCharacter* Character = GetDaniCharacter())
    {
        ERaceType Race = ERaceType::Human;
        if (RaceName.Equals("Giant")) Race = ERaceType::Giant;
        else if (RaceName.Equals("Oni")) Race = ERaceType::Oni;

        Character->GetRaceComponent()->InitializeRace(Race, bIsSamurai);
    }
}

// ─── PLAYER COMMANDS ───────────────────────────────────────────────
void ADaniGameController::ToggleCombatMode()
{
    if (ADaniCharacter* Character = GetDaniCharacter())
    {
        Character->ToggleCombatMode();
    }
}