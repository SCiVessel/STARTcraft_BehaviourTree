#include "SCV_ACTION_BUILD_COMMANDCENTER.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_BUILD_COMMANDCENTER::SCV_ACTION_BUILD_COMMANDCENTER(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_COMMANDCENTER::Evaluate(void* data)
{
    return ReturnState(BuildCommandCenter(data)); 
}

std::string SCV_ACTION_BUILD_COMMANDCENTER::GetDescription()
{
    return "BUILD COMMAND CENTER";
}


BT_NODE::State SCV_ACTION_BUILD_COMMANDCENTER::BuildCommandCenter(void* data)
{
    Data* pData = (Data*)data;

    // let's build a Command Center;
    const BWAPI::UnitType BuildCommand = BWAPI::UnitTypes::Terran_Command_Center;

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

    BWAPI::TilePosition buildPos;
    bool isBuildable = false;
    // Ask BWAPI for a building location near the desired position for the type
    for (size_t i = 0; i < pData->tilesOfExpansions.size(); i++)
    {
        if (BWAPI::Broodwar->canBuildHere(pData->tilesOfExpansions[i], BWAPI::UnitTypes::Terran_Command_Center))
        {
            buildPos = pData->tilesOfExpansions[i];
            isBuildable = true;
            break;
        }
    }

    if (isBuildable == false)
    {
        return BT_NODE::FAILURE;
    }

    BWAPI::Unitset myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto unit : myUnits)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
        {
            if (unit->getOrderTargetPosition() == BWAPI::Position(buildPos))
            {
                return BT_NODE::FAILURE;
            }
            else if (unit->getOrder() == BWAPI::UnitCommandTypes::Build)
            {
                if (unit->getBuildUnit()->getTilePosition() == buildPos)
                {
                    return BT_NODE::FAILURE;
                }
            }
        }
    }

    auto& chokePath = BWEM::Map::Instance().GetNearestArea(buildPos)->ChokePoints();
    for (auto& choke : chokePath)
    {
        if (choke->BlockingNeutral() != nullptr)
        {
            if (choke->BlockingNeutral()->IsMineral())
            {
                Tools::SmartRightClick(builder, choke->BlockingNeutral()->Unit());
                return BT_NODE::FAILURE;
            }
        }
    }

    //if the position is yet to be explored, send a worker to the location first
    if (!BWAPI::Broodwar->isExplored(buildPos))
    {
        
        builder->move(BWAPI::Position(buildPos));
        return BT_NODE::FAILURE;
    }

    const bool startedBuilding = builder->build(BuildCommand, buildPos);

    // Remove from the list only after the building process starts
    pData->unitsFarmingMinerals[index].erase(builder);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building Command Center");



    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}