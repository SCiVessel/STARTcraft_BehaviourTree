#include "SP_DECO_CONDITION_NOT_ENOUGH_WRAITH.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SP_DECO_CONDITION_NOT_ENOUGH_WRAITH::SP_DECO_CONDITION_NOT_ENOUGH_WRAITH(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughWraith) {}


std::string SP_DECO_CONDITION_NOT_ENOUGH_WRAITH::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_WRAITH";
}

bool SP_DECO_CONDITION_NOT_ENOUGH_WRAITH::IsThereNotEnoughWraith(void* data)
{
    Data* pData = (Data*)data;

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 150 or BWAPI::Broodwar->self()->gas() < 100 or unusedSupply < 4)
    {
        return false;
    }

    auto units = BWAPI::Broodwar->self()->getUnits();
    int solders = 0;
    for (auto u : units)
    {
        if (u->canAttack() and u->getType() != BWAPI::UnitTypes::Terran_SCV)
            solders++;
    }
    int wraiths = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Wraith, units);
    if (wraiths <= solders / 3)
        return true;
    else
        return false;

    return false;
}
