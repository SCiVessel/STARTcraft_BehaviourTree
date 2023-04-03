#include "AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR::AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchCaduceusreactor) {}


std::string AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR::GetDescription()
{
    return "DECO CONDITION RESEARCH CADUCEUSREACTOR";
}

bool AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR::canResearchCaduceusreactor(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Caduceus_Reactor) > 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 150 and gas < 150)
    {
        return false;
    }

    int battlecruisers = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Battlecruiser, BWAPI::Broodwar->self()->getUnits());
    if (battlecruisers >= 3)
    {
        return true;
    }

    return false;
}
