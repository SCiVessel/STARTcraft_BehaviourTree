#include "AR_ACTION_UPGRADE_VEHICLEARMOR_LV2.h"
#include "Tools.h"
#include "Data.h"

AR_ACTION_UPGRADE_VEHICLEARMOR_LV2::AR_ACTION_UPGRADE_VEHICLEARMOR_LV2(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AR_ACTION_UPGRADE_VEHICLEARMOR_LV2::Evaluate(void* data)
{
    return ReturnState(actionResearchVehiclearmorlv2(data));
}

std::string AR_ACTION_UPGRADE_VEHICLEARMOR_LV2::GetDescription()
{
    return "ACTION RESEARCH VEHICLEARMOR LV2";
}

BT_NODE::State AR_ACTION_UPGRADE_VEHICLEARMOR_LV2::actionResearchVehiclearmorlv2(void* data)
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
        if (armory->canUpgrade(BWAPI::UpgradeTypes::Terran_Vehicle_Plating))
        {
            armory->upgrade(BWAPI::UpgradeTypes::Terran_Vehicle_Plating);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}