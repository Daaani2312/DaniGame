#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DaniJobSystem.generated.h"

UENUM(BlueprintType)
enum class EJobID : uint8
{
    None = 0,
    OrderGuardians = 1,    // Guardianes del Orden
    WorldNobles = 2,       // Nobles Mundiales
    CommerceCrafts = 3     // Trabajos Comerciales y Artesanales
};

UENUM(BlueprintType)
enum class ERankID : uint8
{
    None = 0,
    // Guardianes del Orden
    AdmiralOfTheGuard = 1,
    CorsairCaptain = 2,
    NavyLieutenant = 3,
    BreezeGuard = 4,
    WindHound = 5,
    KrakenSquadron = 6,
    BaySentinel = 7,
    NoviceSailor = 8,

    // Nobles Mundiales
    GrandCorsair = 1,
    TideBaron = 2,
    CrownSquire = 3,
    StarsEmissary = 4,

    // Trabajos Comerciales
    Merchant = 1,
    Fisherman = 2,
    Artisan = 3,
    Cook = 4,
    Blacksmith = 5,
    Shipwright = 6,
    WeaponsDealer = 7,
    StreetVendor = 8,
    Navigator = 9,
    Explorer = 10,
    Mercenary = 11
};

USTRUCT(BlueprintType)
struct FJobRankInfo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EJobID JobID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ERankID RankID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText JobName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText RankName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanHireFire; // Si este rango puede contratar/despedir
};

UCLASS(Blueprintable, BlueprintType)
class DANIGAME_API UDaniJobSystem : public UObject
{
    GENERATED_BODY()

public:
    UDaniJobSystem();

    // Inicializa el sistema con datos
    UFUNCTION(BlueprintCallable, Category = "Dani|Jobs")
    void InitializeJobSystem(UDataTable* JobDataTable);

    // Obtener información del trabajo
    UFUNCTION(BlueprintCallable, Category = "Dani|Jobs")
    bool GetJobInfo(EJobID JobID, ERankID RankID, FJobRankInfo& OutInfo) const;

    // Verificar permisos
    UFUNCTION(BlueprintCallable, Category = "Dani|Jobs")
    bool CanHireFire(EJobID RequesterJob, ERankID RequesterRank, EJobID TargetJob) const;

    // Cambiar rango de un jugador (solo dentro del mismo JobID)
    UFUNCTION(BlueprintCallable, Category = "Dani|Jobs")
    bool ChangePlayerRank(EJobID JobID, ERankID NewRankID);

    // Añadir nuevo trabajo (desde editor o administrador)
    UFUNCTION(BlueprintCallable, Category = "Dani|Jobs")
    void AddNewJob(EJobID NewJobID, const FText& JobName);

    // Añadir nuevo rango a un trabajo existente
    UFUNCTION(BlueprintCallable, Category = "Dani|Jobs")
    void AddNewRank(EJobID JobID, ERankID NewRankID, const FText& RankName, bool bCanHireFire = false);

protected:
    UPROPERTY()
    UDataTable* JobData;

    // Mapa interno para búsquedas rápidas
    TMap<TTuple<EJobID, ERankID>, FJobRankInfo> JobRankMap;
}; #pragma once
