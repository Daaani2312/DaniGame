#include "DaniGameMode.h"
#include "PJ1.h"
#include "DaniPlayerController.h"

ADaniGameMode::ADaniGameMode()
{
    DefaultPawnClass = ADaniCharacter::StaticClass();
    PlayerControllerClass = ADaniPlayerController::StaticClass();
}

void ADaniGameMode::BeginPlay()
{
    Super::BeginPlay();
}
