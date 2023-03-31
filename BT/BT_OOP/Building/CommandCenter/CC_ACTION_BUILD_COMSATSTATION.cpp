#include "CC_ACTION_BUILD_COMSATSTATION.h"
#include "Tools.h"
#include "Data.h"

CC_ACTION_BUILD_COMSATSTATION::CC_ACTION_BUILD_COMSATSTATION(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State CC_ACTION_BUILD_COMSATSTATION::Evaluate(void* data)
{
    return ReturnState(buildComsatStation(data)); 
}

std::string CC_ACTION_BUILD_COMSATSTATION::GetDescription()
{
    return "BUILD COMSATSTATION";
}


BT_NODE::State CC_ACTION_BUILD_COMSATSTATION::buildComsatStation(void* data)
{
    Data* pData = (Data*)data;

    for (int i = 0; i < pData->CommandCenters.size(); i++)
    {
        bool startedBuilding = pData->CommandCenters[i]->buildAddon(BWAPI::UnitTypes::Terran_Comsat_Station);
        if (startedBuilding)
        {
            BWAPI::Broodwar->printf("Started Building ComsatStation");
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}