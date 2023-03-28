#include "BA_DECO_CONDITION_NOT_ENOUGH_MEDIC.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BA_DECO_CONDITION_NOT_ENOUGH_MEDIC::BA_DECO_CONDITION_NOT_ENOUGH_MEDIC(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughMedic) {}


std::string BA_DECO_CONDITION_NOT_ENOUGH_MEDIC::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_MEDIC";
}

bool BA_DECO_CONDITION_NOT_ENOUGH_MEDIC::IsThereNotEnoughMedic(void *data)
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

    auto medics = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Medic, units);
    auto marines = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Marine, units);

    if (medics * 6 < marines)
    {
        return true;
    }

    return false;
}
