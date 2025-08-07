#include "DaniPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

ADaniPlayerController::ADaniPlayerController()
{
}

void ADaniPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Input/IMC_Default.IMC_Default")), 0);
    }
}

void ADaniPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_Pause.IA_Pause")), ETriggerEvent::Triggered, this, &ADaniPlayerController::TogglePauseMenu);
    }
}

void ADaniPlayerController::TogglePauseMenu()
{
    // Implement pause menu logic
}