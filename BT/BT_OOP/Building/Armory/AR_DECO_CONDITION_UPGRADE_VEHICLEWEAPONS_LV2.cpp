#include "AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2::AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeVehicleweaponslv2) {}


std::string AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2::GetDescription()
{
    return "DECO CONDITION UPGRADE VEHICLEWEAPONS LV2";
}

bool AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2::canUpgradeVehicleweaponslv2(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Vehicle_Weapons) != 1)
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
