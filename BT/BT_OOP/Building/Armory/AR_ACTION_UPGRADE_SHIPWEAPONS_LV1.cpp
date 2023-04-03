#include "AR_ACTION_UPGRADE_SHIPWEAPONS_LV1.h"
#include "Tools.h"
#include "Data.h"

AR_ACTION_UPGRADE_SHIPWEAPONS_LV1::AR_ACTION_UPGRADE_SHIPWEAPONS_LV1(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AR_ACTION_UPGRADE_SHIPWEAPONS_LV1::Evaluate(void* data)
{
    return ReturnState(actionResearchShipweaponslv1(data));
}

std::string AR_ACTION_UPGRADE_SHIPWEAPONS_LV1::GetDescription()
{
    return "ACTION RESEARCH SHIPWEAPONS LV1";
}

BT_NODE::State AR_ACTION_UPGRADE_SHIPWEAPONS_LV1::actionResearchShipweaponslv1(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit armory;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Armory && unit->isCompleted())
        {
            if (unit->isResearching())
            {
                continue;
            }
            armory = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (armory->canUpgrade(BWAPI::UpgradeTypes::Terran_Ship_Weapons))
        {
            armory->upgrade(BWAPI::UpgradeTypes::Terran_Ship_Weapons);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}