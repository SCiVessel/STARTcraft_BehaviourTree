#include "AC_DECO_CONDITION_RESEARCH_RESTORATION.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AC_DECO_CONDITION_RESEARCH_RESTORATION::AC_DECO_CONDITION_RESEARCH_RESTORATION(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchRestoration) {}


std::string AC_DECO_CONDITION_RESEARCH_RESTORATION::GetDescription()
{
    return "DECO CONDITION RESEARCH RESTORATION";
}

bool AC_DECO_CONDITION_RESEARCH_RESTORATION::canResearchRestoration(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Restoration))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    if (BWAPI::Broodwar->elapsedTime() > MID_GAME)
    {
        return true;
    }

    return false;
}
