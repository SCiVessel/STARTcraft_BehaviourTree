#include "EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1::EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canUpgradeInfantryarmorlv1) {}


std::string EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1::GetDescription()
{
    return "DECO CONDITION UPGRADE INFANTRYARMOR LV1";
}

bool EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1::canUpgradeInfantryarmorlv1(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Terran_Infantry_Armor) != 0)
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
