#include "SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY::SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughFactory) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_FACTORY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY::IsThereNotEnoughFactory(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 200)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->gas() < 100)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of Factory
    int existingFactory = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Factory, unitSet);
    // Do nothing if we already have enough factory
    if (existingFactory >= pData->nWantedFactoryTotal)
    {
        return false;
    }

    // Get the amount of Barracks
    int existingBarracks = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Barracks, unitSet);
    // Do nothing ig we have no Barracks
    if (existingBarracks < 1)
    {
        return false;
    }


    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Factory)
        {
            existingFactory += 1;
            
            if (existingFactory >= pData->nWantedFactoryTotal)
            {
                break;
            }
        }
    }

 
    // Return true if we need to build more factory
    return existingFactory < pData->nWantedFactoryTotal;

}
