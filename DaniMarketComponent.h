#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniMarketComponent.generated.h"

USTRUCT(BlueprintType)
struct FMarketItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentStock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BasePrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentPrice;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniMarketComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniMarketComponent();

    UFUNCTION(BlueprintCallable)
    bool BuyItem(APJ1* Buyer, FName ItemID, int32 Quantity);

    UFUNCTION(BlueprintCallable)
    bool SellItem(APJ1* Seller, FName ItemID, int32 Quantity);

    UFUNCTION(BlueprintCallable)
    float GetItemPrice(FName ItemID) const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Market")
    TArray<FMarketItem> MarketItems;

private:
    void UpdatePrices();
    FMarketItem* FindItem(FName ItemID);
}; #pragma once
