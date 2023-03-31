#include "FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP::FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughMachineShop) {}


std::string FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP::GetDescription()
{
    return "FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP";
}

bool FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP::IsThereNotEnoughMachineShop(void *data)
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

    // Do nothing if we have no Factory
    int existingFactory = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Factory, unitSet);
    if (existingFactory < 1)
    {
        return false;
    }

    // Get the amount of MachineShop
    int existingMachineShop = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Machine_Shop, unitSet);
    // Do nothing if we already have enough MachineShop
    if (existingMachineShop >= existingFactory)
    {
        return false;
    }

    // Return true if we need to build more CS
    return true;
}
