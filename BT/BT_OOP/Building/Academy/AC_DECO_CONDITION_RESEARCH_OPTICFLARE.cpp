#include "AC_DECO_CONDITION_RESEARCH_OPTICFLARE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AC_DECO_CONDITION_RESEARCH_OPTICFLARE::AC_DECO_CONDITION_RESEARCH_OPTICFLARE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchOpticflare) {}


std::string AC_DECO_CONDITION_RESEARCH_OPTICFLARE::GetDescription()
{
    return "DECO CONDITION RESEARCH OPTICFLARE";
}

bool AC_DECO_CONDITION_RESEARCH_OPTICFLARE::canResearchOpticflare(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Optical_Flare))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 && gas < 100)
    {
        return false;
    }

    if (minerals >= 4000 && gas >= 4000)
    {
        return true;
    }

    return false;
}
