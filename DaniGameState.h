#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DaniGameState.generated.h"

UCLASS()
class DANIGAME_API ADaniGameState : public AGameState
{
    GENERATED_BODY()

public:
    ADaniGameState();

protected:
    FTimerHandle DailyPaymentTimer;

    void ProcessDailyPayments();

    virtual void BeginPlay() override;
}; #pragma once
