#include "SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY::SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughArmory) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_ARMORY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY::IsThereNotEnoughArmory(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 100)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->gas() < 50)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of Armory
    int existingArmory = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Armory, unitSet);
    // Do nothing if we already have enough armory
    if (existingArmory >= pData->nWantedArmoryTotal)
    {
        return false;
    }

    // Get the amount of Factory
    int existingFactory = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Factory, unitSet);
    // Do nothing ig we have no Factory
    if (existingFactory < 1)
    {
        return false;
    }


    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Armory)
        {
            existingArmory += 1;
            
            if (existingArmory >= pData->nWantedArmoryTotal)
            {
                break;
            }
        }
    }

    // Return true if we need to build more factory
    return existingArmory < pData->nWantedArmoryTotal;
}
