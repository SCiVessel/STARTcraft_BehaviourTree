#include "SCV_ACTION_BUILD_REFINERY.h"
#include "Tools.h"
#include "Data.h"

// REFINERY
// Refinery

SCV_ACTION_BUILD_REFINERY::SCV_ACTION_BUILD_REFINERY(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_REFINERY::Evaluate(void* data)
{
    return ReturnState(BuildRefinery(data));
}

std::string SCV_ACTION_BUILD_REFINERY::GetDescription()
{
    return "BUILD REFINERY";
}


BT_NODE::State SCV_ACTION_BUILD_REFINERY::BuildRefinery(void* data)
{
    Data* pData = (Data*)data;

    // let's build a Refinery
    const BWAPI::UnitType BuildRefinery = BWAPI::UnitTypes::Terran_Refinery;
    
    // Get a location that we want to build the building next to
    BWAPI::Unit geyser = *begin(pData->availableGeysers);
    BWAPI::TilePosition desiredPos = geyser->getTilePosition();

    // Get the closest command center to this geyser
    BWAPI::Unit commandCenter = geyser->getClosestUnit(BWAPI::Filter::IsResourceDepot, 128);
    BWAPI::TilePosition locationCommandCenter = commandCenter->getTilePosition();
    int indexCommandCenter = 0;
    for (int i=0; i<pData->tilePositionCommandCenters.size(); i++)
    {
        if (pData->tilePositionCommandCenters[i] == locationCommandCenter)
        {
            indexCommandCenter = i;
            break;
        }
    }

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

    BWAPI::Unitset myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto unit : myUnits)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
        {
            if (unit->getOrderTargetPosition() == BWAPI::Position(desiredPos))
            {
                return BT_NODE::FAILURE;
            }
            
            if (unit->getOrder() == BWAPI::UnitCommandTypes::Build)
            {
                if (unit->getBuildUnit()->getTilePosition() == desiredPos)
                {
                    return BT_NODE::FAILURE;
                }
            }
        }
    }

    if (!BWAPI::Broodwar->canBuildHere(desiredPos, BuildRefinery))
    {
        return BT_NODE::FAILURE;
    }

    const bool startedBuilding = builder->build(BuildRefinery, desiredPos);

    // Remove from the list only after the building process starts
    pData->unitsFarmingMinerals[indexCommandCenter].erase(builder);
    pData->unitsFarmingGeysers[indexCommandCenter].insert(builder);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building Refinery");



    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}