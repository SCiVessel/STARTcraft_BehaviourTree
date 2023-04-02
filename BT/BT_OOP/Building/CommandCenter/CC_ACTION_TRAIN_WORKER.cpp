#include "CC_ACTION_TRAIN_WORKER.h"
#include "Tools.h"
#include "Data.h"

CC_ACTION_TRAIN_WORKER::CC_ACTION_TRAIN_WORKER(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State CC_ACTION_TRAIN_WORKER::Evaluate(void* data)
{
    return ReturnState(TrainWorker(data));
}

std::string CC_ACTION_TRAIN_WORKER::GetDescription()
{
    return "TRAIN WORKER";
}


BT_NODE::State CC_ACTION_TRAIN_WORKER::TrainWorker(void* data)
{
    Data* pData = (Data*)data;

    std::vector<BWAPI::Unit> CommandCenters;

    // For each unit that we own
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == BWAPI::UnitTypes::Terran_Command_Center && unit->isCompleted())
        {
            CommandCenters.push_back(unit);
        }
    }

    for (auto& unit : CommandCenters)
    {
        if (unit && !unit->isTraining())
        {
            unit->train(BWAPI::UnitTypes::Terran_SCV);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}