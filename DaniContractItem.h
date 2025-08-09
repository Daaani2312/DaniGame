#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DaniContractItem.generated.h"

UCLASS()
class DANIGAME_API ADaniContractItem : public AActor
{
    GENERATED_BODY()

public:
    ADaniContractItem();

    // Tipo de contrato que otorga este �tem
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Contract")
    TSubclassOf<class UDaniContractBase> GrantedContract;

    // Interactuar con el �tem
    UFUNCTION(BlueprintCallable, Category = "Contract")
    void OnInteract(class APJ1* InteractingPlayer);
}; #pragma once
