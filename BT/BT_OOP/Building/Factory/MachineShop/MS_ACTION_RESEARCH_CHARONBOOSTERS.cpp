#include "MS_ACTION_RESEARCH_CHARONBOOSTERS.h"
#include "Tools.h"
#include "Data.h"

MS_ACTION_RESEARCH_CHARONBOOSTERS::MS_ACTION_RESEARCH_CHARONBOOSTERS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State MS_ACTION_RESEARCH_CHARONBOOSTERS::Evaluate(void* data)
{
    return ReturnState(actionResearchCharonboosters(data));
}

std::string MS_ACTION_RESEARCH_CHARONBOOSTERS::GetDescription()
{
    return "ACTION RESEARCH CHARONBOOSTERS";
}

BT_NODE::State MS_ACTION_RESEARCH_CHARONBOOSTERS::actionResearchCharonboosters(void* data)
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
        if (machineshop->canUpgrade(BWAPI::UpgradeTypes::Charon_Boosters))
        {
            machineshop->upgrade(BWAPI::UpgradeTypes::Charon_Boosters);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}