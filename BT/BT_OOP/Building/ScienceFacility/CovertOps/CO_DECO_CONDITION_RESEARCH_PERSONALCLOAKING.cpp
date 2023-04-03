#include "CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING::CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchPersonalcloaking) {}


std::string CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING::GetDescription()
{
    return "DECO CONDITION RESEARCH PERSONALCLOAKING";
}

bool CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING::canResearchPersonalcloaking(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= EARLY_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Personnel_Cloaking))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    return true;
}
