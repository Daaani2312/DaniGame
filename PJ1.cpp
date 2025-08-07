#include "DaniCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADaniCharacter::ADaniCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    bReplicateMovement = true;

    StatsComponent = CreateDefaultSubobject<UDaniStatsComponent>(TEXT("StatsComponent"));
    HakiComponent = CreateDefaultSubobject<UDaniHakiComponent>(TEXT("HakiComponent"));
}

void ADaniCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ADaniCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADaniCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADaniCharacter::MoveRight);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADaniCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADaniCharacter::SprintEnd);

    PlayerInputComponent->BindAction("ArmamentHaki", IE_Pressed, this, &ADaniCharacter::ActivateArmamentHaki);
    PlayerInputComponent->BindAction("ObservationHaki", IE_Pressed, this, &ADaniCharacter::ActivateObservationHaki);
    PlayerInputComponent->BindAction("ConquerorsHaki", IE_Pressed, this, &ADaniCharacter::ActivateConquerorsHaki);
}

void ADaniCharacter::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void ADaniCharacter::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void ADaniCharacter::SprintStart()
{
    if (StatsComponent && StatsComponent->HasEnoughStamina(10.0f))
    {
        GetCharacterMovement()->MaxWalkSpeed = StatsComponent->GetModifiedStats().SprintSpeed;
    }
}

void ADaniCharacter::SprintEnd()
{
    if (StatsComponent)
    {
        GetCharacterMovement()->MaxWalkSpeed = StatsComponent->GetModifiedStats().WalkSpeed;
    }
}

void ADaniCharacter::ActivateArmamentHaki()
{
    if (HakiComponent)
    {
        HakiComponent->ActivateArmamentHaki();
    }
}

void ADaniCharacter::ActivateObservationHaki()
{
    if (HakiComponent)
    {
        HakiComponent->ActivateObservationHaki();
    }
}

void ADaniCharacter::ActivateConquerorsHaki()
{
    if (HakiComponent)
    {
        HakiComponent->ActivateConquerorsHaki();
    }
}
void ADaniCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HakiComponent && HakiComponent->IsHakiActive(EHakiType::Observation))
    {
        // Aquí procesa efectos continuos de haki de observación, por ejemplo detectar enemigos o alertar
    }
}
