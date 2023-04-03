#include "SCV_ACTION_BUILD_SUPPLY_PROVIDER.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_BUILD_SUPPLY_PROVIDER::SCV_ACTION_BUILD_SUPPLY_PROVIDER(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_BUILD_SUPPLY_PROVIDER::Evaluate(void* data)
{
    return ReturnState(BuildSupplyProvider(data));
}

std::string SCV_ACTION_BUILD_SUPPLY_PROVIDER::GetDescription()
{
    return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State SCV_ACTION_BUILD_SUPPLY_PROVIDER::BuildSupplyProvider(void* data)
{
    Data* pData = (Data*)data;

    // let's build a supply provider
    const BWAPI::UnitType supplyProviderType = BWAPI::Broodwar->self()->getRace().getSupplyProvider();

    const bool startedBuilding = Tools::BuildBuilding(supplyProviderType);

    if (startedBuilding)
        BWAPI::Broodwar->printf("Started Building %s", supplyProviderType.getName().c_str());

    return startedBuilding ? BT_NODE::SUCCESS:BT_NODE::FAILURE;
}