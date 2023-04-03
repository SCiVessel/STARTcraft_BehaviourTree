#include "SF_ACTION_RESEARCH_TITANREACTOR.h"
#include "Tools.h"
#include "Data.h"

SF_ACTION_RESEARCH_TITANREACTOR::SF_ACTION_RESEARCH_TITANREACTOR(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State SF_ACTION_RESEARCH_TITANREACTOR::Evaluate(void* data)
{
    return ReturnState(actionResearchTitanreactor(data));
}

std::string SF_ACTION_RESEARCH_TITANREACTOR::GetDescription()
{
    return "ACTION RESEARCH TITANREACTOR";
}

BT_NODE::State SF_ACTION_RESEARCH_TITANREACTOR::actionResearchTitanreactor(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit sciencefacility;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Facility && unit->isCompleted())
        {
            sciencefacility = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (sciencefacility->canUpgrade(BWAPI::UpgradeTypes::Titan_Reactor))
        {
            sciencefacility->upgrade(BWAPI::UpgradeTypes::Titan_Reactor);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}