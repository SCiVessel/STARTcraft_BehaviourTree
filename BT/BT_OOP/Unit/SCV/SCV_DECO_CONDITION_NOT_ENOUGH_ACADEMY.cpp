#include "SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY::SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughAcademy) {}


std::string SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_ACADEMY";
}

bool SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY::IsThereNotEnoughAcademy(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 150)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->gas() < 50)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of Academy
    int existingAcademy = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Academy, unitSet);
    // Do nothing if we already have enough academy
    if (existingAcademy >= 1)
    {
        return false;
    }

    // Get the amount of Barracks
    int existingBarracks = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Barracks, unitSet);
    // Do nothing if we have no Barracks
    if (existingBarracks < 1)
    {
        return false;
    }


    // If the worker is on the task
    for (auto& unit : unitSet)
    {
        if (unit->getType().isWorker() && unit->isConstructing() && unit->getBuildType() == BWAPI::UnitTypes::Terran_Academy)
        {
            existingAcademy += 1;
            
            if (existingAcademy >= 1)
            {
                break;
            }
        }
    }

 
    // Return true if we need to build more Academy
    return existingAcademy < 1;

}
