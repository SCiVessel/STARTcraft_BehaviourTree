#include "FA_ACTION_TRAIN_SIEGETANK.h"
#include "Tools.h"
#include "Data.h"

FA_ACTION_TRAIN_SIEGETANK::FA_ACTION_TRAIN_SIEGETANK(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State FA_ACTION_TRAIN_SIEGETANK::Evaluate(void* data)
{
    return ReturnState(TrainSiegetank(data));
}

std::string FA_ACTION_TRAIN_SIEGETANK::GetDescription()
{
    return "TRAIN SIEGETANK";
}


BT_NODE::State FA_ACTION_TRAIN_SIEGETANK::TrainSiegetank(void* data)
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
            unit->train(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}
