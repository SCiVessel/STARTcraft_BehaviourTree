#include "SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS::SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS::Evaluate(void* data)
{
    return ReturnState(SendIdleWorkerToMinerals(data));
}

std::string SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS::GetDescription()
{
    return "SEND IDLE WORKER TO MINERAL";
}


BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS::SendIdleWorkerToMinerals(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {

            // Get the closet command center
            BWAPI::Unit closetCommandCenter = unit->getClosestUnit(BWAPI::Filter::IsOwned && BWAPI::Filter::IsResourceDepot);
            BWAPI::TilePosition locationCommandCenter = closetCommandCenter->getTilePosition();

            // Get the closest mineral to this command center
            BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(closetCommandCenter, BWAPI::Broodwar->getMinerals());

            int indexCommandCenter = 0;
            for (int i = 0; i < pData->tilePositionCommandCenters.size(); i++)
            {
                if (pData->unitsFarmingMinerals[i].contains(unit))
                {
                    pData->unitsFarmingMinerals[i].erase(unit);
                }

                if (pData->tilePositionCommandCenters[i] == locationCommandCenter)
                {
                    indexCommandCenter = i;
                    break;
                }
            }

            // If the command center already has sufficient workers, move to another command center
            if (pData->unitsFarmingMinerals[indexCommandCenter].size() >= pData->nWantedWorkersFarmingMinerals[indexCommandCenter])
            {
                for (int temp = indexCommandCenter; temp < pData->tilePositionCommandCenters.size(); temp++)
                {
                    if (pData->unitsFarmingMinerals[temp].size() < pData->nWantedWorkersFarmingMinerals[temp])
                    {
                        unit->rightClick(pData->positionCommandCenters[temp]);
                        return BT_NODE::FAILURE;
                    }
                }
            }

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestMineral) {
                for (auto& check : pData->unitsFarmingMinerals)
                {
                    if (check.contains(unit))
                    {
                        check.erase(unit);
                    }
                }
                unit->rightClick(closestMineral);
                // Insert the worker to the list of the designated base
                if (!pData->blockingMinerals.empty())
                {
                    if (pData->blockingMinerals.contains(closestMineral))
                    {
                        return BT_NODE::SUCCESS;
                    }
                }

                pData->unitsFarmingMinerals[indexCommandCenter].insert(unit);
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}