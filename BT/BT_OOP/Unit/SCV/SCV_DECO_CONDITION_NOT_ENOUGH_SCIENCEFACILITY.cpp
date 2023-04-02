#include "SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY::SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughScienceFacility) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SCIENCE_FACILITY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY::IsThereNotEnoughScienceFacility(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 100)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->gas() < 150)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of Science Facility
    int existingScienceFacility = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Science_Facility, unitSet);

    // Do nothing if we already have enough factory
    if (existingScienceFacility >= pData->nWantedScienceFacilityTotal)
    {
        return false;
    }

    // Get the amount of Starport
    int existingStarport = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Starport, unitSet);
    // Do nothing ig we have no Starport
    if (existingStarport < 1)
    {
        return false;
    }


    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && !unit->isIdle() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Science_Facility)
        {
            existingScienceFacility += 1;
            
            if (existingScienceFacility >= pData->nWantedScienceFacilityTotal)
            {
                break;
            }
        }
    }

 
    // Return true if we need to build more factory
    return existingScienceFacility < pData->nWantedScienceFacilityTotal;

}
