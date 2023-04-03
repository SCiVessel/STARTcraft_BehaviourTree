#include "AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1::AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeVehicleweaponslv1) {}


std::string AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1::GetDescription()
{
    return "DECO CONDITION UPGRADE VEHICLEWEAPONS LV1";
}

bool AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1::canUpgradeVehicleweaponslv1(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Vehicle_Weapons) != 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    return true;
}
