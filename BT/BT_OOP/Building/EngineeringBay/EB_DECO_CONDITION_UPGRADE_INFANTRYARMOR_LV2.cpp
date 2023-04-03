#include "EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2::EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeInfantryarmorlv2) {}


std::string EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2::GetDescription()
{
    return "DECO CONDITION UPGRADE INFANTRYARMOR LV2";
}

bool EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2::canUpgradeInfantryarmorlv2(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= EARLY_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Infantry_Armor) != 1)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 175 and gas < 175)
    {
        return false;
    }

    bool found = false;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Facility && unit->isCompleted())
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        return false;
    }

    return true;
}
