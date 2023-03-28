#include "SP_ACTION_TRAIN_DROPSHIP.h"
#include "Tools.h"
#include "Data.h"

SP_ACTION_TRAIN_DROPSHIP::SP_ACTION_TRAIN_DROPSHIP(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State SP_ACTION_TRAIN_DROPSHIP::Evaluate(void* data)
{
    return ReturnState(TrainDropship(data));
}

std::string SP_ACTION_TRAIN_DROPSHIP::GetDescription()
{
    return "TRAIN DROPSHIP";
}


BT_NODE::State SP_ACTION_TRAIN_DROPSHIP::TrainDropship(void* data)
{
    Data* pData = (Data*)data;

    std::vector<BWAPI::Unit> starport;

    // For each unit that we own
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == BWAPI::UnitTypes::Terran_Starport && unit->isCompleted())
        {
            starport.push_back(unit);
        }
    }

    for (auto& unit : starport)
    {
        if (unit && !unit->isTraining())
        {
            unit->train(BWAPI::UnitTypes::Terran_Dropship);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}
