#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniRancherComponent.generated.h"

class AAnimal;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniRancherComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniRancherComponent();

    UFUNCTION(BlueprintCallable)
    bool FeedAnimal(AAnimal* Animal, FName FoodItemID);

    UFUNCTION(BlueprintCallable)
    bool CollectProduct(AAnimal* Animal);

private:
    UPROPERTY(EditDefaultsOnly)
    TMap<FName, float> FoodNutritionValues;
}; #pragma once
