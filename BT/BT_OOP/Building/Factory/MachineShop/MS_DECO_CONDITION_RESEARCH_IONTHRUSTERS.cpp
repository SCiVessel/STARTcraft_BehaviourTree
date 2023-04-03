#include "MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS::MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchIonthrusters) {}


std::string MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS::GetDescription()
{
    return "DECO CONDITION RESEARCH IONTHRUSTERS";
}

bool MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS::canResearchIonthrusters(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Ion_Thrusters) > 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    int vultures = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Vulture, BWAPI::Broodwar->self()->getUnits());
    if (vultures >= 6)
    {
        return true;
    }

    return false;
}
