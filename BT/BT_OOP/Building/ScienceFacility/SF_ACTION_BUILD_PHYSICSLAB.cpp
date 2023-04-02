#include "SF_ACTION_BUILD_PHYSICSLAB.h"
#include "Tools.h"
#include "Data.h"

SF_ACTION_BUILD_PHYSICSLAB::SF_ACTION_BUILD_PHYSICSLAB(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SF_ACTION_BUILD_PHYSICSLAB::Evaluate(void* data)
{
    return ReturnState(buildPhysicsLab(data));
}

std::string SF_ACTION_BUILD_PHYSICSLAB::GetDescription()
{
    return "BUILD PHYSICSLAB";
}


BT_NODE::State SF_ACTION_BUILD_PHYSICSLAB::buildPhysicsLab(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : unitSet)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Facility)
        {
            bool startedBuilding = unit->buildAddon(BWAPI::UnitTypes::Terran_Physics_Lab);
            if (startedBuilding)
            {
                BWAPI::Broodwar->printf("Started Building Physics Lab");
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}