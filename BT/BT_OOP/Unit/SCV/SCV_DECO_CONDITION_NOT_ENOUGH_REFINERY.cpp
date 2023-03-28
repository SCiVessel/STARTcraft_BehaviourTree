#include "SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY::SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughRefinery) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY::GetDescription()
{
    return "SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY::IsThereNotEnoughRefinery(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 100)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Do nothing if we have no barracks
    int existingBarracks = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Barracks, unitSet);
    if (existingBarracks == 0)
    {
        return false;
    }


    int desiredRefineryNum = pData->availableGeysers.size();
    if (desiredRefineryNum == 0)
    {
        return false;
    }

    // If the worker is on the task
    int existingRefinery = 0;
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Refinery)
        {
            existingRefinery += 1;
            
            if (existingRefinery >= desiredRefineryNum)
            {
                break;
            }
        }
    }

    if (existingRefinery >= desiredRefineryNum)
    {
        return false;
    }

    return true;
}
