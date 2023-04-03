#include "CT_ACTION_RESEARCH_CLOAKINGFIELD.h"
#include "Tools.h"
#include "Data.h"

CT_ACTION_RESEARCH_CLOAKINGFIELD::CT_ACTION_RESEARCH_CLOAKINGFIELD(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CT_ACTION_RESEARCH_CLOAKINGFIELD::Evaluate(void* data)
{
    return ReturnState(actionResearchCloakingfield(data));
}

std::string CT_ACTION_RESEARCH_CLOAKINGFIELD::GetDescription()
{
    return "ACTION RESEARCH CLOAKINGFIELD";
}

BT_NODE::State CT_ACTION_RESEARCH_CLOAKINGFIELD::actionResearchCloakingfield(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit controltower;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Control_Tower && unit->isCompleted())
        {
            controltower = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (controltower->canResearch(BWAPI::TechTypes::Cloaking_Field))
        {
            controltower->research(BWAPI::TechTypes::Cloaking_Field);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}