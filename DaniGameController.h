#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DaniGameController.generated.h"

class ADaniCharacter;

UCLASS()
class DANIGAME_API ADaniGameController : public APlayerController
{
    GENERATED_BODY()

public:
    ADaniGameController();

    // ─── ADMIN COMMANDS ────────────────────────────────────────────
    UFUNCTION(Exec, Category = "Admin")
    void AdminSetConquerorWill(bool bEnable);

    UFUNCTION(Exec, Category = "Admin")
    void AdminSetFamily(const FString& FamilyName);

    UFUNCTION(Exec, Category = "Admin")
    void AdminSetRace(const FString& RaceName, bool bIsSamurai = false);

    // ─── PLAYER COMMANDS ───────────────────────────────────────────
    UFUNCTION(Exec, Category = "Player")
    void ToggleCombatMode();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    // Helper functions
    ADaniCharacter* GetDaniCharacter() const;
    void ValidateAdminPrivileges() const;
};