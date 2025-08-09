#pragma once

#include "DaniContractBase.h"
#include "DaniTransformationBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DANIGAME_API UDaniTransformationBase : public UDaniContractBase
{
    GENERATED_BODY()

public:
    UDaniTransformationBase();

    // Formas disponibles
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transformation")
    TArray<FName> TransformationForms;

    // Transformaci�n actual
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transformation")
    FName CurrentForm;

    // M�todos para transformaci�n
    UFUNCTION(BlueprintCallable, Category = "Transformation")
    virtual void Transform(FName FormName);

    UFUNCTION(BlueprintCallable, Category = "Transformation")
    virtual void RevertToHumanForm();

    // Habilidades espec�ficas de forma
    UFUNCTION(BlueprintCallable, Category = "Transformation")
    virtual void ExecuteFormAbility(int32 AbilityIndex);

protected:
    // Estado de transformaci�n
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transformation")
    bool bIsTransformed;
}; #pragma once
