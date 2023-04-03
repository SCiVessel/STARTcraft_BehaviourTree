#include "EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3.h"
#include "Tools.h"
#include "Data.h"

EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3::EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3::Evaluate(void* data)
{
    return ReturnState(actionResearchInfantryweaponslv3(data));
}

std::string EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3::GetDescription()
{
    return "ACTION RESEARCH INFANTRYWEAPONS LV3";
}

BT_NODE::State EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3::actionResearchInfantryweaponslv3(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit engineeringBay;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Engineering_Bay && unit->isCompleted())
        {
            if (unit->isResearching())
            {
                continue;
            }
            engineeringBay = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (engineeringBay->canUpgrade(BWAPI::UpgradeTypes::Terran_Infantry_Weapons))
        {
            engineeringBay->upgrade(BWAPI::UpgradeTypes::Terran_Infantry_Weapons);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}