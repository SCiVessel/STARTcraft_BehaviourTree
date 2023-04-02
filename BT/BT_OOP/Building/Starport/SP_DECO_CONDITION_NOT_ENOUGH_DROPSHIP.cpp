#include "SP_DECO_CONDITION_NOT_ENOUGH_DROPSHIP.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SP_DECO_CONDITION_NOT_ENOUGH_DROPSHIP::SP_DECO_CONDITION_NOT_ENOUGH_DROPSHIP(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughDropship) {}


std::string SP_DECO_CONDITION_NOT_ENOUGH_DROPSHIP::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_DROPSHIP";
}

bool SP_DECO_CONDITION_NOT_ENOUGH_DROPSHIP::IsThereNotEnoughDropship(void *data)
{
    Data* pData = (Data*)data;
    auto units = BWAPI::Broodwar->self()->getUnits();

    int Controltowers = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Control_Tower, units);
    if (Controltowers < 1)
    {
        return false;
    }

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 100 or BWAPI::Broodwar->self()->gas() < 100 or unusedSupply < 4)
    {
        return false;
    }

    bool isStuck = false;
    for (auto u : units)
    {
        if (u->isStuck())
        {
            isStuck = true;
            break;
        }
    }

    if (BWAPI::Broodwar->self()->minerals() > 1500 and isStuck)
        return true;
    else
        return false;

    return false;
}
