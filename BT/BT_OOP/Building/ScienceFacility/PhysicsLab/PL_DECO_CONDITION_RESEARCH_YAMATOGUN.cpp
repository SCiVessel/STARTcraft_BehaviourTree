#include "PL_DECO_CONDITION_RESEARCH_YAMATOGUN.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

PL_DECO_CONDITION_RESEARCH_YAMATOGUN::PL_DECO_CONDITION_RESEARCH_YAMATOGUN(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchYamatogun) {}


std::string PL_DECO_CONDITION_RESEARCH_YAMATOGUN::GetDescription()
{
    return "DECO CONDITION RESEARCH YAMATOGUN";
}

bool PL_DECO_CONDITION_RESEARCH_YAMATOGUN::canResearchYamatogun(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Yamato_Gun))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
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
