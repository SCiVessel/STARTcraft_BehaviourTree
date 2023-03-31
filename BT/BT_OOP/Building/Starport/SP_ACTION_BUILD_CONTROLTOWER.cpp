#include "SP_ACTION_BUILD_CONTROLTOWER.h"
#include "Tools.h"
#include "Data.h"

SP_ACTION_BUILD_CONTROLTOWER::SP_ACTION_BUILD_CONTROLTOWER(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SP_ACTION_BUILD_CONTROLTOWER::Evaluate(void* data)
{
    return ReturnState(buildControlTower(data));
}

std::string SP_ACTION_BUILD_CONTROLTOWER::GetDescription()
{
    return "BUILD CONTROLTOWER";
}


BT_NODE::State SP_ACTION_BUILD_CONTROLTOWER::buildControlTower(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : unitSet)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Starport)
        {
            bool startedBuilding = unit->buildAddon(BWAPI::UnitTypes::Terran_Control_Tower);
            if (startedBuilding)
            {
                BWAPI::Broodwar->printf("Started Building Control Tower");
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}