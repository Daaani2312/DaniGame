#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniContractComponent.generated.h"

class UDaniContractBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniContractComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniContractComponent();

    // Contrato activo
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Contract")
    UDaniContractBase* ActiveContract;

    // Adquirir nuevo contrato
    UFUNCTION(BlueprintCallable, Category = "Contract")
    void AcquireContract(TSubclassOf<UDaniContractBase> ContractClass);

    // Eliminar contrato actual
    UFUNCTION(BlueprintCallable, Category = "Contract")
    void RemoveCurrentContract();

    // Actualización por frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
}; #pragma once
