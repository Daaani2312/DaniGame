#include "DaniGameState.h"
#include "PJ1.h"
#include "DaniPlayerJobComponent.h"

ADaniGameState::ADaniGameState()
{
    // Cada 20 minutos de juego (ajustable)
    GetWorldTimerManager().SetTimer(DailyPaymentTimer, this, &ADaniGameState::ProcessDailyPayments, 1200.0f, true);
}

void ADaniGameState::ProcessDailyPayments()
{
    for (APlayerState* PlayerState : PlayerArray)
    {
        if (APJ1* Player = Cast<APJ1>(PlayerState->GetPawn()))
        {
            if (UDaniPlayerJobComponent* JobComponent = Player->FindComponentByClass<UDaniPlayerJobComponent>())
            {
                JobComponent->PayDailyWages();
            }
        }
    }
}