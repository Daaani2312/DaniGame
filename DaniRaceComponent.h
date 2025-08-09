#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniRaceSystem.h"
#include "DaniRaceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniRaceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniRaceComponent();

    UFUNCTION(BlueprintCallable, Category = "Race")
    void InitializeRace(ERaceType Race, bool bIsSamurai = false);

    UFUNCTION(BlueprintCallable, Category = "Race")
    float GetTrainingMultiplier(FName StatName, ERegionType CurrentRegion) const;

    UFUNCTION(BlueprintPure, Category = "Race")
    ERaceType GetRaceType() const { return CurrentRace; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Race")
    UDaniRaceData* RaceDataAsset;

private:
    ERaceType CurrentRace;
    bool bIsSamurai;
}; #pragma once
