#include "SCV_ACTION_BUILD_FACTORY.h"
#include "Tools.h"
#include "Data.h"

// FACTORY
// Factory

SCV_ACTION_BUILD_FACTORY::SCV_ACTION_BUILD_FACTORY(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_FACTORY::Evaluate(void* data)
{
    return ReturnState(BuildFactory(data));
}

std::string SCV_ACTION_BUILD_FACTORY::GetDescription()
{
    return "BUILD FACTORY";
}


BT_NODE::State SCV_ACTION_BUILD_FACTORY::BuildFactory(void* data)
{
    Data* pData = (Data*)data;

    // let's build a factory;
    const BWAPI::UnitType BuildFactory = BWAPI::UnitTypes::Terran_Factory;

    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    auto it = pData->unitsFarmingMinerals[0].begin();
    if (it == pData->unitsFarmingMinerals[0].end())
    {
        return BT_NODE::FAILURE;
    }
    BWAPI::Unit builder = *it;
    
    // Get a location that we want to build the building next to
    BWAPI::TilePosition desiredPos = BWAPI::Broodwar->self()->getStartLocation();

    // Ask BWAPI for a building location near the desired position for the type
    int maxBuildRange = 128;
    bool buildingOnCreep = BuildFactory.requiresCreep();
    BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(BuildFactory, desiredPos, maxBuildRange, buildingOnCreep);
    if (!BWAPI::Broodwar->getUnitsOnTile(buildPos).empty())
    {
        return  BT_NODE::FAILURE;
    }

    const bool startedBuilding = builder->build(BuildFactory, buildPos);


    // Remove from the list only after the building process starts
    pData->unitsFarmingMinerals[0].erase(it);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building Factory");



    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}