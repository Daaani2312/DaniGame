#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DaniStatsComponent.h"
#include "DaniHakiComponent.h"
#include "DaniCharacter.generated.h"

UCLASS()
class DANIGAME_API ADaniCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADaniCharacter();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniStatsComponent* StatsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDaniHakiComponent* HakiComponent;

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Movement
    void MoveForward(float Value);
    void MoveRight(float Value);
    void SprintStart();
    void SprintEnd();

    // Haki Abilities
    void ActivateArmamentHaki();
    void ActivateObservationHaki();
    void ActivateConquerorsHaki();
};
