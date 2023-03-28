#include "SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT::SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughStarport) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_STARPORT";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT::IsThereNotEnoughStarport(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 150)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->gas() < 100)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of starport
    int existingStarport = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Starport, unitSet);
    // Do nothing if we already have enough starport
    if (existingStarport >= pData->nWantedStarportTotal)
    {
        return false;
    }

    // Get the amount of factory
    int existingFactory = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Factory, unitSet);
    // Do nothing ig we have no factory
    if (existingFactory < 1)
    {
        return false;
    }


    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Starport)
        {
            existingStarport += 1;
            
            if (existingStarport >= pData->nWantedStarportTotal)
            {
                break;
            }
        }
    }

 
    // Return true if we need to build more starport
    return existingStarport < pData->nWantedStarportTotal;

}
