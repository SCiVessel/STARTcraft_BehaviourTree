#include "AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1::AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeShiparmorlv1) {}


std::string AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1::GetDescription()
{
    return "DECO CONDITION UPGRADE SHIPARMOR LV1";
}

bool AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1::canUpgradeShiparmorlv1(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Ship_Plating) != 0)
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
