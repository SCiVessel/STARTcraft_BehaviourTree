#include "SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS::SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS::Evaluate(void* data)
{
    return ReturnState(SendIdleWorkerToGeysers(data));
}

std::string SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS::GetDescription()
{
    return "SEND IDLE WORKER TO GEYSERS";
}


BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS::SendIdleWorkerToGeysers(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            // Get the closest mineral to this worker unit
            BWAPI::Unit closestGeyser = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getGeysers());

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestGeyser) {
                unit->rightClick(closestGeyser);
                pData->unitsFarmingGeysers.insert(unit);
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}