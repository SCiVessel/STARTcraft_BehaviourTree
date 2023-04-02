#include "SF_ACTION_BUILD_COVERTOPS.h"
#include "Tools.h"
#include "Data.h"

SF_ACTION_BUILD_COVERTOPS::SF_ACTION_BUILD_COVERTOPS(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SF_ACTION_BUILD_COVERTOPS::Evaluate(void* data)
{
    return ReturnState(buildCovertOps(data));
}

std::string SF_ACTION_BUILD_COVERTOPS::GetDescription()
{
    return "BUILD COVERTOPS";
}


BT_NODE::State SF_ACTION_BUILD_COVERTOPS::buildCovertOps(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : unitSet)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Facility)
        {
            bool startedBuilding = unit->buildAddon(BWAPI::UnitTypes::Terran_Covert_Ops);
            if (startedBuilding)
            {
                BWAPI::Broodwar->printf("Started Building CovertOps");
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}