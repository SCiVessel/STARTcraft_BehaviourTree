#include "SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT::SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT::Evaluate(void* data)
{
    return ReturnState(SendIdleWorkerToScout(data));
}

std::string SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT::GetDescription()
{
    return "SEND IDLE WORKER TO SCOUT";
}


BT_NODE::State SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT::SendIdleWorkerToScout(void* data)
{
    Data* pData = (Data*)data;

    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            unit->move(pData->enemySpawnLocation);
            pData->scoutUnits.insert(unit);
            BWAPI::Broodwar->printf("Early Game Scouting");
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}