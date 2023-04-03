#include "MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS::MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchCharonboosters) {}


std::string MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS::GetDescription()
{
    return "DECO CONDITION RESEARCH CHARONBOOSTERS";
}

bool MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS::canResearchCharonboosters(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Charon_Boosters) > 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    int goliaths = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Goliath, BWAPI::Broodwar->self()->getUnits());
    if (goliaths >= 6)
    {
        return true;
    }

    return false;
}
