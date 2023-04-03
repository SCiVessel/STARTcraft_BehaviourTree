#include "SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY::SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY::Evaluate(void* data)
{
    return ReturnState(SendIdleWorkerToRefinery(data));
}

std::string SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY::GetDescription()
{
    return "SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY";
}


BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY::SendIdleWorkerToRefinery(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    
    // check if we do have a refinery
    bool flag = 0;
    for (auto& unit : myUnits)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Refinery)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        return BT_NODE::FAILURE;
    }

    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            // Get the closest refinery to this worker unit
            BWAPI::Unit closestRefinery = unit->getClosestUnit(BWAPI::Filter::IsRefinery && BWAPI::Filter::IsOwned);

            // Get the closet command center
            BWAPI::Unit closetCommandCenter = closestRefinery->getClosestUnit(BWAPI::Filter::IsResourceDepot && BWAPI::Filter::IsOwned);
            BWAPI::TilePosition locationCommandCenter = closetCommandCenter->getTilePosition();

            int indexCommandCenter = 0;
            for (int i = 0; i < pData->tilePositionCommandCenters.size(); i++)
            {
                if (pData->tilePositionCommandCenters[i] == locationCommandCenter)
                {
                    indexCommandCenter = i;
                    break;
                }
            }

            // If the command center already has sufficient workers, move to another command center
            if (pData->unitsFarmingGeysers[indexCommandCenter].size() >= pData->nWantedWorkersFarmingGeysers[indexCommandCenter])
            {
                for (int temp = indexCommandCenter; temp < pData->tilePositionCommandCenters.size(); temp++)
                {
                    if (pData->unitsFarmingGeysers[temp].size() < pData->nWantedWorkersFarmingGeysers[temp])
                    {
                        unit->rightClick(pData->positionCommandCenters[temp]);
                        return BT_NODE::FAILURE;
                    }
                }
            }

            // If a valid refinery was found, right click it with the unit in order to start harvesting
            if (closestRefinery)
            {
                for (auto& check : pData->unitsFarmingGeysers)
                {
                    if (check.contains(unit))
                    {
                        check.erase(unit);
                    }
                }
                Tools::SmartRightClick(unit, closestRefinery);
                // Insert the worker to the list of the designated base
                pData->unitsFarmingGeysers[indexCommandCenter].insert(unit);
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::FAILURE;
}