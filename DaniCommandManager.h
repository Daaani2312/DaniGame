#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DaniRaceComponent.h"
#include "Engine/EngineTypes.h"
#include "DaniCommandManager.generated.h"

class APJ1;

DECLARE_DELEGATE_TwoParams(FCommandDelegate, const TArray<FString>&, APlayerController*);

USTRUCT(BlueprintType)
struct FCommandInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Commands")
    FString CommandName;

    UPROPERTY(BlueprintReadOnly, Category = "Commands")
    FString Description;

    UPROPERTY(BlueprintReadOnly, Category = "Commands")
    FString Usage;
};

UCLASS(Blueprintable, BlueprintType)
class DANIGAME_API UDaniCommandManager : public UObject
{
    GENERATED_BODY()

public:
    UDaniCommandManager();

    // Inicializa el sistema de comandos
    UFUNCTION(BlueprintCallable, Category = "Commands")
    void InitializeCommandSystem(APlayerController* OwningPlayer);

    // Ejecuta un comando del juego
    UFUNCTION(BlueprintCallable, Category = "Commands")
    void ExecuteCommand(const FString& Command, const TArray<FString>& Args, APlayerController* PlayerController);

    // Obtiene todos los comandos registrados
    UFUNCTION(BlueprintCallable, Category = "Commands")
    TArray<FCommandInfo> GetRegisteredCommands() const;

    // Envía un mensaje del sistema al jugador
    UFUNCTION(BlueprintCallable, Category = "Commands")
    void SendSystemMessage(APlayerController* TargetPlayer, const FString& Message, FLinearColor Color = FLinearColor::Green, float DisplayTime = 5.0f);

protected:
    // Registra todos los comandos disponibles
    void RegisterAllCommands();

    // Registra un solo comando
    void RegisterCommand(const FString& Command, const FString& Description, const FString& Usage, FCommandDelegate Delegate);

private:
    // Implementaciones de comandos
    void Command_GiveMoney(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_TakeMoney(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_GiveStat(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_GiveRace(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_GiveAbility(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_GiveConqueror(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_Imprison(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_Kill(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_Bring(const TArray<FString>& Args, APlayerController* PlayerController);
    void Command_Freeze(const TArray<FString>& Args, APlayerController* PlayerController);

    // Funciones auxiliares
    APlayerController* FindPlayerByName(const FString& PlayerName, APlayerController* ExcludingPlayer = nullptr) const;
    bool ValidateAdminStatus(APlayerController* PlayerController) const;
    void LogCommandUsage(APlayerController* PlayerController, const FString& Command) const;

    UPROPERTY()
    APlayerController* OwningPlayerController;

    TMap<FString, FCommandInfo> CommandRegistry;
};