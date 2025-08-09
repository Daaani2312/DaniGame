#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DaniCombatTypes.h"
#include "PJ1.generated.h"

// Forward declarations de componentes
class UDaniStatsComponent;
class UDaniHakiComponent;
class UDaniCombatComponent;
class UDaniPlayerJobComponent;

UCLASS()
class DANIGAME_API APJ1 : public ACharacter
{
    GENERATED_BODY()

public:
    APJ1();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // ─── Componentes principales ───────────────────────────────
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniStatsComponent* StatsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniHakiComponent* HakiComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniPlayerJobComponent* JobComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniMarketComponent* MarketComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniRancherComponent* RancherComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniCombatComponent* CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UDaniRaceComponent* RaceComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UDaniSocialComponent* SocialComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UDaniInventoryComponent* InventoryComponent;

    // ─── NUEVO: Componente de trabajos ──────────────────────────
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniPlayerJobComponent* JobComponent;

private:
    // ─── Input Bindings ─────────────────────────────────────────
    void SetupMovementInput();
    void SetupHakiInput();
    void SetupCombatInput();

    // ─── Combat Actions ─────────────────────────────────────────
    void ToggleCombatMode();
    void ExecuteBasicAttack();
    void StartBlocking();
    void StopBlocking();
    void ReloadWeapon();
    void ActivateCombatAbility();
    void SwitchToSwordStyle();
    void SwitchToFistStyle();

    // ─── Event Handlers ─────────────────────────────────────────
    UFUNCTION()
    void HandleCombatModeEnabled();

    UFUNCTION()
    void HandleCombatModeDisabled();

    UFUNCTION()
    void HandleCombatStyleChanged(TSubclassOf<UDaniCombatStyleBase> OldStyle, TSubclassOf<UDaniCombatStyleBase> NewStyle);

    // ─── Helpers ────────────────────────────────────────────────
    bool CanExecuteCombatAction() const;
};
