#include "BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS::BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughBarracks) {}


std::string BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_BARRACKS";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS::IsThereNotEnoughBarracks(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 150)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of Barracks
    int existingBarracks = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Barracks, unitSet);
    // Do nothing if we already have enough barracks
    if (existingBarracks >= pData->nWantedBarracksTotal)
    {
        return false;
    }

    // Get the amount of Supply Depots
   
    // Do nothing ig we have no supply depots
    if (Tools::GetTotalSupply(false) <= SUPPLY_PROVIDED_BY_CC)
    {
        return false;
    }


    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Barracks)
        {
            existingBarracks += 1;
            
            if (existingBarracks >= pData->nWantedBarracksTotal)
            {
                break;
            }
        }
    }

 
    // Return true if we need to build more barracks
    return existingBarracks < pData->nWantedBarracksTotal;

}
