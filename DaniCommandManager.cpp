#include "DaniCommandManager.h"
#include "PJ1.h"
#include "DaniPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UDaniCommandManager::UDaniCommandManager()
{
    // Constructor
}

void UDaniCommandManager::InitializeCommandSystem(APlayerController* OwningPlayer)
{
    this->OwningPlayerController = OwningPlayer;
    RegisterAllCommands();
}

void UDaniCommandManager::RegisterAllCommands()
{
    // Comandos de dinero
    RegisterCommand(
        "givemoney",
        "Dar dinero a un jugador",
        "givemoney [NombreJugador] [Cantidad]",
        FCommandDelegate::CreateUObject(this, &UDaniCommandManager::Command_GiveMoney)
    );

    RegisterCommand(
        "takemoney",
        "Quitar dinero a un jugador",
        "takemoney [NombreJugador] [Cantidad]",
        FCommandDelegate::CreateUObject(this, &UDaniCommandManager::Command_TakeMoney)
    );

    // Comandos de personaje
    RegisterCommand(
        "givestat",
        "Modificar estadísticas del jugador",
        "givestat [NombreJugador] [StatName] [Value]",
        FCommandDelegate::CreateUObject(this, &UDaniCommandManager::Command_GiveStat)
    );

    RegisterCommand(
        "giverace",
        "Cambiar la raza del jugador",
        "giverace [NombreJugador] [RaceName]",
        FCommandDelegate::CreateUObject(this, &UDaniCommandManager::Command_GiveRace)
    );

    // Resto de comandos...
}

void UDaniCommandManager::Command_GiveMoney(const TArray<FString>& Args, APlayerController* PlayerController)
{
    if (!ValidateAdminStatus(PlayerController)) return;

    if (Args.Num() < 2)
    {
        SendSystemMessage(PlayerController, "Uso: givemoney [NombreJugador] [Cantidad]", FLinearColor::Red);
        return;
    }

    APlayerController* TargetPlayer = FindPlayerByName(Args[0], PlayerController);
    if (!TargetPlayer && Args[0] != "self")
    {
        SendSystemMessage(PlayerController, FString::Printf(TEXT("Jugador %s no encontrado"), *Args[0]), FLinearColor::Red);
        return;
    }

    if (TargetPlayer == nullptr)
    {
        TargetPlayer = PlayerController;
    }

    int32 Amount = FCString::Atoi(*Args[1]);
    if (APJ1* Character = TargetPlayer ? Cast<APJ1>(TargetPlayer->GetPawn()) : nullptr)
    {
        Character->AddMoney(Amount);
        SendSystemMessage(PlayerController, FString::Printf(TEXT("Dinero dado: %d a %s"), Amount, *TargetPlayer->PlayerState->GetPlayerName()));
        LogCommandUsage(PlayerController, "givemoney");
    }
}

// Implementaciones restantes de comandos...