#include "CO_ACTION_RESEARCH_LOCKDOWN.h"
#include "Tools.h"
#include "Data.h"

CO_ACTION_RESEARCH_LOCKDOWN::CO_ACTION_RESEARCH_LOCKDOWN(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CO_ACTION_RESEARCH_LOCKDOWN::Evaluate(void* data)
{
    return ReturnState(actionResearchLockdown(data));
}

std::string CO_ACTION_RESEARCH_LOCKDOWN::GetDescription()
{
    return "ACTION RESEARCH LOCKDOWN";
}

BT_NODE::State CO_ACTION_RESEARCH_LOCKDOWN::actionResearchLockdown(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit covertops;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Covert_Ops && unit->isCompleted())
        {
            covertops = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (covertops->canResearch(BWAPI::TechTypes::Lockdown))
        {
            covertops->research(BWAPI::TechTypes::Lockdown);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}