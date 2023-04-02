#include "SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY::SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughEngineeringBay) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY::GetDescription()
{
    return "SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY::IsThereNotEnoughEngineeringBay(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 125)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of eBay
    int existingEngineeringBay = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Engineering_Bay, unitSet);
    // Do nothing if we already have enough eBay
    if (existingEngineeringBay >= pData->nWantedEngineeringBayTotal)
    {
        return false;
    }

    // Get the amount of Barracks
    int existingBarracks = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Barracks, unitSet);
    // Do nothing ig we have no supply depots
    if (existingBarracks < 1)
    {
        return false;
    }

    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Engineering_Bay)
        {
            existingEngineeringBay += 1;
            
            if (existingEngineeringBay >= pData->nWantedEngineeringBayTotal)
            {
                break;
            }
        }
    }

    // Return true if we need to build more eBay
    return existingEngineeringBay < pData->nWantedEngineeringBayTotal;
}
