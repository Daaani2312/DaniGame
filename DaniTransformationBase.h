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

    // Transformación actual
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transformation")
    FName CurrentForm;

    // Métodos para transformación
    UFUNCTION(BlueprintCallable, Category = "Transformation")
    virtual void Transform(FName FormName);

    UFUNCTION(BlueprintCallable, Category = "Transformation")
    virtual void RevertToHumanForm();

    // Habilidades específicas de forma
    UFUNCTION(BlueprintCallable, Category = "Transformation")
    virtual void ExecuteFormAbility(int32 AbilityIndex);

protected:
    // Estado de transformación
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transformation")
    bool bIsTransformed;
}; #pragma once
