#include "MS_DECO_CONDITION_RESEARCH_SPIDERMINE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

MS_DECO_CONDITION_RESEARCH_SPIDERMINE::MS_DECO_CONDITION_RESEARCH_SPIDERMINE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchSpidermine) {}


std::string MS_DECO_CONDITION_RESEARCH_SPIDERMINE::GetDescription()
{
    return "DECO CONDITION RESEARCH SPIDERMINE";
}

bool MS_DECO_CONDITION_RESEARCH_SPIDERMINE::canResearchSpidermine(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Spider_Mines))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Tank_Siege_Mode))
    {
        return true;
    }

    return false;
}
