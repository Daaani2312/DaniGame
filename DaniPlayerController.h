#include "DaniPlayerController.h"
#include "DaniCommandManager.h"
#include "Engine/Console.h"
#include "PJ1.h" // Asegúrate de incluir tu clase de personaje
#include "DaniRaceComponent.h" // Para los comandos de raza
#include "GameFramework/CharacterMovementComponent.h"

ADaniPlayerController::ADaniPlayerController()
{
    // Crear el administrador de comandos
    CommandManager = CreateDefaultSubobject<UCommandManager>(TEXT("CommandManager"));
}

void ADaniPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Configurar el sistema de comandos
    if (GEngine && GEngine->ConsoleClass)
    {
        UConsole* Console = GEngine->ConsoleClass->GetDefaultObject<UConsole>();
        Console->RegisterConsoleAutoCompleteEntries.AddRaw(this, &ADaniPlayerController::RegisterAutoCompleteCommands);
    }
}

void ADaniPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        // Comando para pausa
        InputComponent->BindAction("Pause", IE_Pressed, this, &ADaniPlayerController::TogglePauseMenu);

        // Registrar comandos de consola
        InputComponent->BindConsoleCommand("givemoney",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleGiveMoneyCommand));
        InputComponent->BindConsoleCommand("takemoney",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleTakeMoneyCommand));
        InputComponent->BindConsoleCommand("givestat",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleGiveStatCommand));
        InputComponent->BindConsoleCommand("giverace",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleGiveRaceCommand));
        InputComponent->BindConsoleCommand("giveability",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleGiveAbilityCommand));
        InputComponent->BindConsoleCommand("giveconqueror",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleGiveConquerorCommand));
        InputComponent->BindConsoleCommand("imprison",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleImprisonCommand));
        InputComponent->BindConsoleCommand("kill",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleKillCommand));
        InputComponent->BindConsoleCommand("bring",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleBringCommand));
        InputComponent->BindConsoleCommand("freeze",
            FConsoleCommandWithArgsDelegate::CreateUObject(this, &ADaniPlayerController::HandleFreezeCommand));
    }
}

void ADaniPlayerController::ExecuteGameCommand(const FString& Command, const TArray<FString>& Args)
{
    HandleConsoleCommand(Command, Args);
}

void ADaniPlayerController::HandleConsoleCommand(const FString& Command, const TArray<FString>& Args)
{
    if (CommandManager)
    {
        CommandManager->ExecuteCommand(Command, Args, this);
    }
}

void ADaniPlayerController::RegisterAutoCompleteCommands(TArray<FAutoCompleteCommand>& Commands) const
{
    static const TArray<FAutoCompleteCommand> AutoCompleteList = {
        {"givemoney", "Give money to player. Usage: givemoney [PlayerName] [Amount]"},
        {"takemoney", "Take money from player. Usage: takemoney [PlayerName] [Amount]"},
        {"givestat", "Give stat to player. Usage: givestat [PlayerName] [StatName] [Value]"},
        {"giverace", "Set player race. Usage: giverace [PlayerName] [RaceName]"},
        {"giveability", "Give ability to player. Usage: giveability [PlayerName] [AbilityName]"},
        {"giveconqueror", "Set conqueror status. Usage: giveconqueror [PlayerName] [1/0]"},
        {"imprison", "Imprison player. Usage: imprison [PlayerName]"},
        {"kill", "Kill player. Usage: kill [PlayerName]"},
        {"bring", "Teleport player to you. Usage: bring [PlayerName]"},
        {"freeze", "Freeze/unfreeze player. Usage: freeze [PlayerName] [1/0]"}
    };

    Commands.Append(AutoCompleteList);
}

// Implementaciones específicas de cada comando
void ADaniPlayerController::HandleGiveMoneyCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 2)
    {
        int32 Amount = FCString::Atoi(*Args[1]);
        HandleConsoleCommand("givemoney", Args);
    }
}

void ADaniPlayerController::HandleTakeMoneyCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 2)
    {
        HandleConsoleCommand("takemoney", Args);
    }
}

void ADaniPlayerController::HandleGiveStatCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 3)
    {
        HandleConsoleCommand("givestat", Args);
    }
}

void ADaniPlayerController::HandleGiveRaceCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 2)
    {
        HandleConsoleCommand("giverace", Args);
    }
}

void ADaniPlayerController::HandleGiveAbilityCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 2)
    {
        HandleConsoleCommand("giveability", Args);
    }
}

void ADaniPlayerController::HandleGiveConquerorCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 2)
    {
        HandleConsoleCommand("giveconqueror", Args);
    }
}

void ADaniPlayerController::HandleImprisonCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 1)
    {
        HandleConsoleCommand("imprison", Args);
    }
}

void ADaniPlayerController::HandleKillCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 1)
    {
        HandleConsoleCommand("kill", Args);
    }
}

void ADaniPlayerController::HandleBringCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 1)
    {
        HandleConsoleCommand("bring", Args);
    }
}

void ADaniPlayerController::HandleFreezeCommand(const TArray<FString>& Args)
{
    if (Args.Num() >= 2)
    {
        HandleConsoleCommand("freeze", Args);
    }
}

void ADaniPlayerController::TogglePauseMenu()
{
    // Tu implementación existente del menú de pausa
}