#include "EB_ACTION_UPGRADE_INFANTRYARMOR_LV1.h"
#include "Tools.h"
#include "Data.h"

EB_ACTION_UPGRADE_INFANTRYARMOR_LV1::EB_ACTION_UPGRADE_INFANTRYARMOR_LV1(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State EB_ACTION_UPGRADE_INFANTRYARMOR_LV1::Evaluate(void* data)
{
    return ReturnState(actionResearchInfantryarmorlv1(data));
}

std::string EB_ACTION_UPGRADE_INFANTRYARMOR_LV1::GetDescription()
{
    return "ACTION RESEARCH INFANTRYARMOR LV1";
}

BT_NODE::State EB_ACTION_UPGRADE_INFANTRYARMOR_LV1::actionResearchInfantryarmorlv1(void* data)
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
        if (engineeringBay->canUpgrade(BWAPI::UpgradeTypes::Terran_Infantry_Armor))
        {
            engineeringBay->upgrade(BWAPI::UpgradeTypes::Terran_Infantry_Armor);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}