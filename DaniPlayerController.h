#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DaniPlayerController.generated.h"

UCLASS()
class DANIGAME_API ADaniPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ADaniPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void TogglePauseMenu();
};