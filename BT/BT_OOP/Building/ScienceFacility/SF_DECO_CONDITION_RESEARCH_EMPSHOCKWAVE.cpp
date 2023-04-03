#include "SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE::SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchEmpshockwave) {}


std::string SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE::GetDescription()
{
    return "DECO CONDITION RESEARCH EMPSHOCKWAVE";
}

bool SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE::canResearchEmpshockwave(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::EMP_Shockwave))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 200 and gas < 200)
    {
        return false;
    }

    return true;
}
