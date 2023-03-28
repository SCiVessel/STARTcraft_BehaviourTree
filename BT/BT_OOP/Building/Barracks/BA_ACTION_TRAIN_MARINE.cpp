#include "BA_ACTION_TRAIN_MARINE.h"
#include "Tools.h"
#include "Data.h"

BA_ACTION_TRAIN_MARINE::BA_ACTION_TRAIN_MARINE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BA_ACTION_TRAIN_MARINE::Evaluate(void* data)
{
    return ReturnState(TrainMarine(data));
}

std::string BA_ACTION_TRAIN_MARINE::GetDescription()
{
    return "TRAIN MARINE";
}


BT_NODE::State BA_ACTION_TRAIN_MARINE::TrainMarine(void* data)
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
            unit->train(BWAPI::UnitTypes::Terran_Marine);
            BWAPI::Error error = BWAPI::Broodwar->getLastError();
            if (error != BWAPI::Errors::None)
                return BT_NODE::FAILURE;
            else return BT_NODE::SUCCESS;
        }
    }
    
    return BT_NODE::FAILURE;
}