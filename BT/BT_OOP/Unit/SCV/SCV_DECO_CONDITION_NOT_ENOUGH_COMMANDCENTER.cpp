#include "SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER::SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughCommandCenter) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_ACADEMY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER::IsThereNotEnoughCommandCenter(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 400)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of Academy
    int existingCommandCenter = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Command_Center, unitSet);
    // Do nothing if we already have enough academy
    if (existingCommandCenter >= pData->nWantedCommandCenterForTheMoment)
    {
        return false;
    }

    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && unit->isConstructing() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Command_Center)
        {
            existingCommandCenter += 1;
            
            if (existingCommandCenter >= 1)
            {
                break;
            }
        }
    }
 
    // Return true if we need to build more Command Center
    return existingCommandCenter < pData->nWantedCommandCenterForTheMoment;
}
