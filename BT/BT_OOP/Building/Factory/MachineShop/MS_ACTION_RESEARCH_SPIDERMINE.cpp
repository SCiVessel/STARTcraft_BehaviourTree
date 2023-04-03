#include "MS_ACTION_RESEARCH_SPIDERMINE.h"
#include "Tools.h"
#include "Data.h"

MS_ACTION_RESEARCH_SPIDERMINE::MS_ACTION_RESEARCH_SPIDERMINE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State MS_ACTION_RESEARCH_SPIDERMINE::Evaluate(void* data)
{
    return ReturnState(actionResearchSpidermine(data));
}

std::string MS_ACTION_RESEARCH_SPIDERMINE::GetDescription()
{
    return "ACTION RESEARCH SPIDERMINE";
}

BT_NODE::State MS_ACTION_RESEARCH_SPIDERMINE::actionResearchSpidermine(void* data)
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
        if (machineshop->canResearch(BWAPI::TechTypes::Spider_Mines))
        {
            machineshop->research(BWAPI::TechTypes::Spider_Mines);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}