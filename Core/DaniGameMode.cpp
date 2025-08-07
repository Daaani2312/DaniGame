#include "DaniGameMode.h"
#include "DaniCharacter.h"
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
