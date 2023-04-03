#include "CO_DECO_CONDITION_RESEARCH_LOCKDOWN.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CO_DECO_CONDITION_RESEARCH_LOCKDOWN::CO_DECO_CONDITION_RESEARCH_LOCKDOWN(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchLockdown) {}


std::string CO_DECO_CONDITION_RESEARCH_LOCKDOWN::GetDescription()
{
    return "DECO CONDITION RESEARCH LOCKDOWN";
}

bool CO_DECO_CONDITION_RESEARCH_LOCKDOWN::canResearchLockdown(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Lockdown))
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
