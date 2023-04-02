#include "SCV_ACTION_BUILD_ACADEMY.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_BUILD_ACADEMY::SCV_ACTION_BUILD_ACADEMY(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_ACADEMY::Evaluate(void* data)
{
    return ReturnState(BuildAcademy(data)); 
}

std::string SCV_ACTION_BUILD_ACADEMY::GetDescription()
{
    return "BUILD ACADEMY";
}


BT_NODE::State SCV_ACTION_BUILD_ACADEMY::BuildAcademy(void* data)
{
    Data* pData = (Data*)data;

    // let's build a Academy;
    const BWAPI::UnitType BuildAcademy = BWAPI::UnitTypes::Terran_Academy;

    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    BWAPI::Unit builder;
    unsigned int index;

    bool flag = false;
    for (size_t i = 0; i < pData->unitsFarmingMinerals.size(); i++)
    {
        auto it = pData->unitsFarmingMinerals[i].begin();
        if (it != pData->unitsFarmingMinerals[i].end())
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
    bool buildingOnCreep = BuildAcademy.requiresCreep();
    BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(BuildAcademy, desiredPos, maxBuildRange, buildingOnCreep);
    if (!BWAPI::Broodwar->getUnitsOnTile(buildPos).empty())
    {
        return  BT_NODE::FAILURE;
    }

    const bool startedBuilding = builder->build(BuildAcademy, buildPos);


    // Remove from the list only after the building process starts
    pData->unitsFarmingMinerals[index].erase(builder);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building Academy");



    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}