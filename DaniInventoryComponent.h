#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniInventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniInventoryComponent();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void MarkItemAsSecure(int32 ItemId);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UnmarkItemAsSecure(int32 ItemId);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    TArray<int32> GetLootableItems() const;

private:
    UPROPERTY()
    TArray<int32> SecureItems;

    UPROPERTY()
    TArray<int32> RegularItems;
}; #pragma once
