#include "AC_DECO_CONDITION_RESEARCH_U238SHELLS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AC_DECO_CONDITION_RESEARCH_U238SHELLS::AC_DECO_CONDITION_RESEARCH_U238SHELLS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchU238shells) {}


std::string AC_DECO_CONDITION_RESEARCH_U238SHELLS::GetDescription()
{
    return "DECO CONDITION RESEARCH U238SHELLS";
}

bool AC_DECO_CONDITION_RESEARCH_U238SHELLS::canResearchU238shells(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::U_238_Shells) > 0)
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
