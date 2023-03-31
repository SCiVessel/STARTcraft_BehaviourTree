#include "FA_ACTION_BUILD_MACHINESHOP.h"
#include "Tools.h"
#include "Data.h"

FA_ACTION_BUILD_MACHINESHOP::FA_ACTION_BUILD_MACHINESHOP(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State FA_ACTION_BUILD_MACHINESHOP::Evaluate(void* data)
{
    return ReturnState(buildMachineShop(data));
}

std::string FA_ACTION_BUILD_MACHINESHOP::GetDescription()
{
    return "BUILD MACHINESHOP";
}


BT_NODE::State FA_ACTION_BUILD_MACHINESHOP::buildMachineShop(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : unitSet)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Factory)
        {
            bool startedBuilding = unit->buildAddon(BWAPI::UnitTypes::Terran_Machine_Shop);
            if (startedBuilding)
            {
                BWAPI::Broodwar->printf("Started Building Machine Shop");
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}