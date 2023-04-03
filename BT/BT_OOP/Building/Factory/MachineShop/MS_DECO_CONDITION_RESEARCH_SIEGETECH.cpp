#include "MS_DECO_CONDITION_RESEARCH_SIEGETECH.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

MS_DECO_CONDITION_RESEARCH_SIEGETECH::MS_DECO_CONDITION_RESEARCH_SIEGETECH(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchSiegetech) {}


std::string MS_DECO_CONDITION_RESEARCH_SIEGETECH::GetDescription()
{
    return "DECO CONDITION RESEARCH SIEGETECH";
}

bool MS_DECO_CONDITION_RESEARCH_SIEGETECH::canResearchSiegetech(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Tank_Siege_Mode))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 150 and gas < 150)
    {
        return false;
    }

    return true;
}
