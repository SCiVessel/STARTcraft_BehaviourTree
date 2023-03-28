#include "SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL::SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughSciencevessel) {}


std::string SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL";
}

bool SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL::IsThereNotEnoughSciencevessel(void* data)
{
    Data* pData = (Data*)data;

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 100 or BWAPI::Broodwar->self()->gas() < 225 or unusedSupply < 4)
    {
        return false;
    }

    auto units = BWAPI::Broodwar->self()->getUnits();
    int timePeriod = BWAPI::Broodwar->elapsedTime();
    int scienceVessels = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Science_Vessel, units);
    if (timePeriod <= EARLY_GAME and scienceVessels < 1)
        return true;
    else if (timePeriod <= MID_GAME and scienceVessels < 2)
        return true;
    else if (scienceVessels < 3)
        return true;
    else
        return false;

    return false;
}
