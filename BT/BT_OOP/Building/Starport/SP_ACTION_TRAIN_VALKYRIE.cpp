#include "SP_ACTION_TRAIN_VALKYRIE.h"
#include "Tools.h"
#include "Data.h"

SP_ACTION_TRAIN_VALKYRIE::SP_ACTION_TRAIN_VALKYRIE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State SP_ACTION_TRAIN_VALKYRIE::Evaluate(void* data)
{
    return ReturnState(TrainValkyrie(data));
}

std::string SP_ACTION_TRAIN_VALKYRIE::GetDescription()
{
    return "TRAIN VALKYRIE";
}


BT_NODE::State SP_ACTION_TRAIN_VALKYRIE::TrainValkyrie(void* data)
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
            unit->train(BWAPI::UnitTypes::Terran_Valkyrie);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}
