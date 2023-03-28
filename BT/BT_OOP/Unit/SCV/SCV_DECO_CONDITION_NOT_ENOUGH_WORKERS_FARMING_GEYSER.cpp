#include "SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER::SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughWorkersFarmingGeyser) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER::GetDescription()
{
    return "SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER::IsThereNotEnoughWorkersFarmingGeyser(void *data)
{
    Data* pData = (Data*)data;

    BWAPI::Unitset temp;
    for (int i = 0; i < pData->nWantedWorkersFarmingGeysers.size(); i++)
    {
        if (pData->unitsFarmingGeysers[i].size() < pData->nWantedWorkersFarmingGeysers[i])
        {
            temp = pData->CommandCenters[i]->getUnitsInRadius(128, BWAPI::Filter::IsRefinery);
            if (!temp.empty())
            {
                for (auto& refinery : temp)
                {
                    if (refinery->isCompleted())
                    {
                        return true;
                    }
                }
                
            }
        }
    }

    return false;
}
