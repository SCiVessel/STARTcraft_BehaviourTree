#include "MS_ACTION_RESEARCH_SIEGETECH.h"
#include "Tools.h"
#include "Data.h"

MS_ACTION_RESEARCH_SIEGETECH::MS_ACTION_RESEARCH_SIEGETECH(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State MS_ACTION_RESEARCH_SIEGETECH::Evaluate(void* data)
{
    return ReturnState(actionResearchSiegetech(data));
}

std::string MS_ACTION_RESEARCH_SIEGETECH::GetDescription()
{
    return "ACTION RESEARCH SIEGETECH";
}

BT_NODE::State MS_ACTION_RESEARCH_SIEGETECH::actionResearchSiegetech(void* data)
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
        if (machineshop->canResearch(BWAPI::TechTypes::Tank_Siege_Mode))
        {
            machineshop->research(BWAPI::TechTypes::Tank_Siege_Mode);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}