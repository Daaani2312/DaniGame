#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DaniGameMode.generated.h"

UCLASS()
class DANIGAME_API ADaniGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ADaniGameMode();

protected:
    virtual void BeginPlay() override;
};
