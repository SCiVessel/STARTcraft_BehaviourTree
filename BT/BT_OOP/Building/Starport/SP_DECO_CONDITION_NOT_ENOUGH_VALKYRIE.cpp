#include "SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE::SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughValkyrie) {}


std::string SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_VALKYRIE";
}

bool SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE::IsThereNotEnoughValkyrie(void* data)
{
    Data* pData = (Data*)data;
    auto units = BWAPI::Broodwar->self()->getUnits();

    int Controltowers = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Control_Tower, units);
    int Armories = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Armory, units);
    if (Controltowers < 1 || Armories < 1)
    {
        return false;
    }

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 250 or BWAPI::Broodwar->self()->gas() < 125 or unusedSupply < 6)
    {
        return false;
    }

    int valkyries = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Valkyrie, units);
    if (valkyries > 3)
        return false;

    auto enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
    int enemyAirUnits = 0;
    for (auto eu : enemyUnits)
        if (eu->isFlying())
            enemyAirUnits++;
    
    if (enemyAirUnits > 12)
        return true;
    else
        return false;

    return false;
}
