#include "SCV_ACTION_BUILD_UNFINISHED_BUILDING.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_BUILD_UNFINISHED_BUILDING::SCV_ACTION_BUILD_UNFINISHED_BUILDING(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_UNFINISHED_BUILDING::Evaluate(void* data)
{
    return ReturnState(BuildUnfinished(data));
}

std::string SCV_ACTION_BUILD_UNFINISHED_BUILDING::GetDescription()
{
    return "BUILD UNFINISHED";
}


BT_NODE::State SCV_ACTION_BUILD_UNFINISHED_BUILDING::BuildUnfinished(void* data)
{
    Data* pData = (Data*)data;

    // Do nothing if no unfinished buildings
    bool unfinishedFlag = false;
    BWAPI::Unit unfinishedBuilding;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if ((unit->getType().isBuilding()) && (!unit->isCompleted()))
        {
            if (!unit->isBeingConstructed())
            {
                unfinishedBuilding = unit;
                unfinishedFlag = true;
                break;
            }
        }
    }

    if (unfinishedFlag == false)
    {
        return BT_NODE::FAILURE;
    }
    // Get a unit that we own that is of the given type so it can build
    // If we can't find a valid builder unit, then we have to cancel the building
    BWAPI::Unit builder;
    unsigned int index;

    bool flag = false;
    for (size_t i = 0; i < pData->unitsFarmingMinerals.size(); i++)
    {
        auto it = pData->unitsFarmingMinerals[i].begin();
        if (it != pData->unitsFarmingMinerals[i].end() && (pData->stuckUnits.empty() || (!pData->stuckUnits.contains(*it))))
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
            if (unit->getOrder() == BWAPI::UnitCommandTypes::Build)
            {
                if (unit->getBuildUnit() == unfinishedBuilding)
                {
                    return BT_NODE::FAILURE;
                }
            }

            if (unit->getOrderTargetPosition() == unfinishedBuilding->getPosition())
            {
                return BT_NODE::FAILURE;
            }
        }
    }

    Tools::SmartRightClick(builder, unfinishedBuilding);

    // Remove from the list only after the building process starts
    pData->unitsFarmingMinerals[index].erase(builder);

    BWAPI::Broodwar->printf("Continue Building Unfinished Building");

    return BT_NODE::SUCCESS;
}