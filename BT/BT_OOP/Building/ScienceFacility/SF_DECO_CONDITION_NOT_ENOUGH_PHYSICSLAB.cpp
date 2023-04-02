#include "SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB::SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughPhysicsLab) {}


std::string SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB::GetDescription()
{
    return "SP_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB";
}

bool SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB::IsThereNotEnoughPhysicsLab(void *data)
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

    // Do nothing if we have no Sience Facility
    int existingSienceFacility = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Science_Facility, unitSet);
    if (existingSienceFacility < 1)
    {
        return false;
    }

    // Get the amount of PhysicsLab
    int existingPhysicsLab = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Physics_Lab, unitSet);
    // Do nothing if we already have enough ControlTower
    if (existingPhysicsLab >= 1)
    {
        return false;
    }

    // Return true if we need to build more PL
    return true;
}
