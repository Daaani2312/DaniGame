#include "DaniJobSystem.h"
#include "Engine/DataTable.h"

UDaniJobSystem::UDaniJobSystem()
{
    // Constructor
}

void UDaniJobSystem::InitializeJobSystem(UDataTable* JobDataTable)
{
    JobData = JobDataTable;
    JobRankMap.Empty();

    if (JobData)
    {
        TArray<FJobRankInfo*> AllJobs;
        JobData->GetAllRows<FJobRankInfo>("", AllJobs);

        for (const FJobRankInfo* JobInfo : AllJobs)
        {
            JobRankMap.Add(TTuple<EJobID, ERankID>(JobInfo->JobID, JobInfo->RankID), *JobInfo);
        }
    }
}

bool UDaniJobSystem::GetJobInfo(EJobID JobID, ERankID RankID, FJobRankInfo& OutInfo) const
{
    const TTuple<EJobID, ERankID> Key(JobID, RankID);
    if (const FJobRankInfo* FoundInfo = JobRankMap.Find(Key))
    {
        OutInfo = *FoundInfo;
        return true;
    }
    return false;
}

bool UDaniJobSystem::CanHireFire(EJobID RequesterJob, ERankID RequesterRank, EJobID TargetJob) const
{
    // Solo puedes contratar/despedir en tu mismo trabajo
    if (RequesterJob != TargetJob) return false;

    FJobRankInfo RequesterInfo;
    if (GetJobInfo(RequesterJob, RequesterRank, RequesterInfo))
    {
        return RequesterInfo.bCanHireFire;
    }
    return false;
}

bool UDaniJobSystem::ChangePlayerRank(EJobID JobID, ERankID NewRankID)
{
    // Aqu� implementar�as la l�gica para cambiar el rango de un jugador
    // Necesitar�as acceso al PlayerState o similar
    return true;
}

void UDaniJobSystem::AddNewJob(EJobID NewJobID, const FText& JobName)
{
    // Implementaci�n para a�adir nuevos trabajos
    // Esto deber�a modificar el DataTable tambi�n
}

void UDaniJobSystem::AddNewRank(EJobID JobID, ERankID NewRankID, const FText& RankName, bool bCanHireFire)
{
    // Implementaci�n para a�adir nuevos rangos
}