#include "BA_ACTION_TRAIN_MEDIC.h"
#include "Tools.h"
#include "Data.h"

BA_ACTION_TRAIN_MEDIC::BA_ACTION_TRAIN_MEDIC(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BA_ACTION_TRAIN_MEDIC::Evaluate(void* data)
{
    return ReturnState(TrainMedic(data));
}

std::string BA_ACTION_TRAIN_MEDIC::GetDescription()
{
    return "TRAIN MEDIC";
}


BT_NODE::State BA_ACTION_TRAIN_MEDIC::TrainMedic(void* data)
{
    Data* pData = (Data*)data;

    std::vector<BWAPI::Unit> barracks;

    // For each unit that we own
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == BWAPI::UnitTypes::Terran_Barracks && unit->isCompleted())
        {
            barracks.push_back(unit);
        }
    }

    for (auto& unit : barracks)
    {
        if (unit && !unit->isTraining())
        {
            unit->train(BWAPI::UnitTypes::Terran_Medic);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}