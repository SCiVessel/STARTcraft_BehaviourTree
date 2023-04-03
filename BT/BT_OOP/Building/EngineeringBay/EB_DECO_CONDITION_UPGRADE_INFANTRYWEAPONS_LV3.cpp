#include "EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3::EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeInfantryweaponslv3) {}


std::string EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3::GetDescription()
{
    return "DECO CONDITION UPGRADE INFANTRYWEAPONS LV3";
}

bool EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3::canUpgradeInfantryweaponslv3(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Infantry_Weapons) != 2)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 250 and gas < 250)
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
