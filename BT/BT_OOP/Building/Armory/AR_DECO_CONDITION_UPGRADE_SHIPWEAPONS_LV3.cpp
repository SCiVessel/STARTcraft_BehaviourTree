#include "AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3::AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeShipweaponslv3) {}


std::string AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3::GetDescription()
{
    return "DECO CONDITION UPGRADE SHIPWEAPONS LV3";
}

bool AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3::canUpgradeShipweaponslv3(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Ship_Weapons) != 2)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 200 and gas < 200)
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
