#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DaniSocialSystem.h"
#include "DaniSocialComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DANIGAME_API UDaniSocialComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDaniSocialComponent();

    UFUNCTION(BlueprintCallable, Category = "Social")
    void InitializeFamily(const FName& FamilyName);

    UFUNCTION(BlueprintCallable, Category = "Social")
    void SetConquerorWill(bool bHasWill);

    UFUNCTION(BlueprintPure, Category = "Social")
    bool HasConquerorWill() const { return bHasConquerorsWill; }

    UFUNCTION(BlueprintPure, Category = "Social")
    float GetTrainingMultiplier() const { return bHasConquerorsWill ? 2.0f : 1.0f; }

private:
    FName CurrentFamily;
    ESocialClass SocialClass;
    bool bHasConquerorsWill = false;
}; #pragma once
