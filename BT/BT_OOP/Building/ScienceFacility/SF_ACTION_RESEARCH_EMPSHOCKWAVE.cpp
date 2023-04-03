#include "SF_ACTION_RESEARCH_EMPSHOCKWAVE.h"
#include "Tools.h"
#include "Data.h"

SF_ACTION_RESEARCH_EMPSHOCKWAVE::SF_ACTION_RESEARCH_EMPSHOCKWAVE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State SF_ACTION_RESEARCH_EMPSHOCKWAVE::Evaluate(void* data)
{
    return ReturnState(actionResearchEmpshockwave(data));
}

std::string SF_ACTION_RESEARCH_EMPSHOCKWAVE::GetDescription()
{
    return "ACTION RESEARCH EMPSHOCKWAVE";
}

BT_NODE::State SF_ACTION_RESEARCH_EMPSHOCKWAVE::actionResearchEmpshockwave(void* data)
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
        if (sciencefacility->canResearch(BWAPI::TechTypes::EMP_Shockwave))
        {
            sciencefacility->research(BWAPI::TechTypes::EMP_Shockwave);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}