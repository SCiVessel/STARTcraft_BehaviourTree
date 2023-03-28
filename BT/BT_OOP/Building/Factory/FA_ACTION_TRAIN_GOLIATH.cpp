#include "FA_ACTION_TRAIN_GOLIATH.h"
#include "Tools.h"
#include "Data.h"

FA_ACTION_TRAIN_GOLIATH::FA_ACTION_TRAIN_GOLIATH(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State FA_ACTION_TRAIN_GOLIATH::Evaluate(void* data)
{
    return ReturnState(TrainGoliath(data));
}

std::string FA_ACTION_TRAIN_GOLIATH::GetDescription()
{
    return "TRAIN GOLIATH";
}


BT_NODE::State FA_ACTION_TRAIN_GOLIATH::TrainGoliath(void* data)
{
    Data* pData = (Data*)data;

    std::vector<BWAPI::Unit> factories;

    // For each unit that we own
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == BWAPI::UnitTypes::Terran_Factory && unit->isCompleted())
        {
            factories.push_back(unit);
        }
    }

    for (auto& unit : factories)
    {
        if (unit && !unit->isTraining())
        {
            unit->train(BWAPI::UnitTypes::Terran_Goliath);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}
