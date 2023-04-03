#include "SF_ACTION_RESEARCH_IRRADIATE.h"
#include "Tools.h"
#include "Data.h"

SF_ACTION_RESEARCH_IRRADIATE::SF_ACTION_RESEARCH_IRRADIATE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State SF_ACTION_RESEARCH_IRRADIATE::Evaluate(void* data)
{
    return ReturnState(actionResearchIrradiate(data));
}

std::string SF_ACTION_RESEARCH_IRRADIATE::GetDescription()
{
    return "ACTION RESEARCH IRRADIATE";
}

BT_NODE::State SF_ACTION_RESEARCH_IRRADIATE::actionResearchIrradiate(void* data)
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
        if (sciencefacility->canResearch(BWAPI::TechTypes::Irradiate))
        {
            sciencefacility->research(BWAPI::TechTypes::Irradiate);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}