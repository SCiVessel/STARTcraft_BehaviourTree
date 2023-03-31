#include "SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER::SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughControlTower) {}


std::string SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER::GetDescription()
{
    return "SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER";
}

bool SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER::IsThereNotEnoughControlTower(void *data)
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

    // Do nothing if we have no Starport
    int existingStarport = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Starport, unitSet);
    if (existingStarport < 1)
    {
        return false;
    }

    // Get the amount of ControlTower
    int existingControlTower = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Control_Tower, unitSet);
    // Do nothing if we already have enough ControlTower
    if (existingControlTower >= existingStarport)
    {
        return false;
    }

    // Return true if we need to build more CT
    return true;
}
