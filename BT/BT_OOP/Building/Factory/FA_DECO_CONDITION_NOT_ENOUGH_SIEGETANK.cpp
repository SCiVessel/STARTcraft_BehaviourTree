#include "FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK::FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughSiegetank) {}


std::string FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SIEGETANK";
}

bool FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK::IsThereNotEnoughSiegetank(void *data)
{
    Data* pData = (Data*)data;

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 150 or BWAPI::Broodwar->self()->gas() < 100 or unusedSupply < 4)
    {
        return false;
    }

    auto units = BWAPI::Broodwar->self()->getUnits();
    int siegetanks = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode, units) + Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode, units);
    int marines = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Marine, units);

    if (siegetanks < marines)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    return false;
}
