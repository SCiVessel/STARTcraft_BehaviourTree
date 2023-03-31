#include "CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION::CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughComsatStation) {}


std::string CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION::GetDescription()
{
    return "CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION";
}

bool CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION::IsThereNotEnoughComsatStation(void *data)
{
    Data* pData = (Data*)data;

    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 50)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->gas() < 50)
    {
        return false;
    }

    // Get all player units
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

    // Get the amount of ComsatStation
    int existingComsatStation = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Comsat_Station, unitSet);
    // Do nothing if we already have enough ComsatStation
    if (existingComsatStation >= 3)
    {
        return false;
    }

    // Do nothing if we have no Academy
    int existingAcademy = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Academy, unitSet);
    if (existingAcademy < 1)
    {
        return false;
    }

    // Do nothing if we have no CC
    if (pData->CommandCenters.size() < 1)
    {
        return false;
    }
 
    // Return true if we need to build more CS
  

    return true;
}
