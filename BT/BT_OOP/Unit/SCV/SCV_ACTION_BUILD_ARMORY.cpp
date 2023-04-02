#include "SCV_ACTION_BUILD_ARMORY.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_BUILD_ARMORY::SCV_ACTION_BUILD_ARMORY(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_ARMORY::Evaluate(void* data)
{
    return ReturnState(BuildArmory(data));
}

std::string SCV_ACTION_BUILD_ARMORY::GetDescription()
{
    return "BUILD ARMORY";
}


BT_NODE::State SCV_ACTION_BUILD_ARMORY::BuildArmory(void* data)
{
    Data* pData = (Data*)data;

    // let's build a Armory;
    const BWAPI::UnitType BuildArmory = BWAPI::UnitTypes::Terran_Armory;

    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    BWAPI::Unit builder;
    unsigned int index;

    bool flag = false;
    for (size_t i = 0; i < pData->unitsFarmingMinerals.size(); i++)
    {
        auto it = pData->unitsFarmingMinerals[i].begin();
        if (it != pData->unitsFarmingMinerals[i].end() && (!pData->stuckUnits.empty() || (!pData->stuckUnits.contains(*it))))
        {
            builder = *it;
            index = i;
            flag = true;
            break;
        }
    }

    if (flag == false)
    {
        return BT_NODE::FAILURE;
    }

    // Get a location that we want to build the building next to
    BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();

    // Ask BWAPI for a building location near the desired position for the type
    int maxBuildRange = 128;
    bool buildingOnCreep = BuildArmory.requiresCreep();
    BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(BuildArmory, desiredPos, maxBuildRange, buildingOnCreep);

    BWAPI::Unitset myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto unit : myUnits)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
        {
            if (unit->getOrderTargetPosition() == BWAPI::Position(buildPos))
            {
                return BT_NODE::FAILURE;
            }
            
            if (unit->getOrder() == BWAPI::UnitCommandTypes::Build)
            {
                if (unit->getBuildUnit()->getTilePosition() == buildPos)
                {
                    return BT_NODE::FAILURE;
                }
            }
        }
    }

    if (!BWAPI::Broodwar->canBuildHere(buildPos, BuildArmory))
    {
        return BT_NODE::FAILURE;
    }

    const bool startedBuilding = builder->build(BuildArmory, buildPos);


    // Remove from the list only after the building process starts
    pData->unitsFarmingMinerals[0].erase(builder);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building Armory");



    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}