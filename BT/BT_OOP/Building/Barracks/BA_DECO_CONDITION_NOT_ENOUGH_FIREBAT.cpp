#include "BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT::BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughFirebat) {}


std::string BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT::GetDescription()
{
    return "BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT";
}

bool BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT::IsThereNotEnoughFirebat(void *data)
{
    Data* pData = (Data*)data;
    
    auto units = BWAPI::Broodwar->self()->getUnits();
    int Academies = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Academy, units);
    if (Academies < 1)
    {
        return false;
    }

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 50 or BWAPI::Broodwar->self()->gas() < 25 or unusedSupply < 2)
    {
        return false;
    }

    int firebats = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Firebat, units);
    int marines = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Marine, units);

    if (firebats * 4 < marines)
    {
        return true;
    }

    return false;
}
