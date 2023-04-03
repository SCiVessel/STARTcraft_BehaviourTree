#include "MS_ACTION_RESEARCH_IONTHRUSTERS.h"
#include "Tools.h"
#include "Data.h"

MS_ACTION_RESEARCH_IONTHRUSTERS::MS_ACTION_RESEARCH_IONTHRUSTERS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State MS_ACTION_RESEARCH_IONTHRUSTERS::Evaluate(void* data)
{
    return ReturnState(actionResearchIonthrusters(data));
}

std::string MS_ACTION_RESEARCH_IONTHRUSTERS::GetDescription()
{
    return "ACTION RESEARCH IONTHRUSTERS";
}

BT_NODE::State MS_ACTION_RESEARCH_IONTHRUSTERS::actionResearchIonthrusters(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit machineshop;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Machine_Shop && unit->isCompleted())
        {
            machineshop = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (machineshop->canUpgrade(BWAPI::UpgradeTypes::Ion_Thrusters))
        {
            machineshop->upgrade(BWAPI::UpgradeTypes::Ion_Thrusters);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}