#include "SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS::SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughCovertOps) {}


std::string SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS::GetDescription()
{
    return "SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS";
}

bool SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS::IsThereNotEnoughCovertOps(void *data)
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

    // Do nothing if we have no Science Facility
    int existingScienceFacility = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Science_Facility, unitSet);
    if (existingScienceFacility < 1)
    {
        return false;
    }

    // Get the amount of CovertOps
    int existingCovertOps = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Covert_Ops, unitSet);
    // Do nothing if we already have enough ControlTower
    if (existingCovertOps >= 1)
    {
        return false;
    }

    // Return true if we need to build more CO
    return true;
}
