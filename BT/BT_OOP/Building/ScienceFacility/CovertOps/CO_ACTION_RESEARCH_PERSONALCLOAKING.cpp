#include "CO_ACTION_RESEARCH_PERSONALCLOAKING.h"
#include "Tools.h"
#include "Data.h"

CO_ACTION_RESEARCH_PERSONALCLOAKING::CO_ACTION_RESEARCH_PERSONALCLOAKING(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CO_ACTION_RESEARCH_PERSONALCLOAKING::Evaluate(void* data)
{
    return ReturnState(actionResearchPersonalcloaking(data));
}

std::string CO_ACTION_RESEARCH_PERSONALCLOAKING::GetDescription()
{
    return "ACTION RESEARCH PERSONALCLOAKING";
}

BT_NODE::State CO_ACTION_RESEARCH_PERSONALCLOAKING::actionResearchPersonalcloaking(void* data)
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
        if (covertops->canResearch(BWAPI::TechTypes::Personnel_Cloaking))
        {
            covertops->research(BWAPI::TechTypes::Personnel_Cloaking);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}