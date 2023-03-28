#include "FA_DECO_CONDITION_NOT_ENOUGH_VULTURE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

FA_DECO_CONDITION_NOT_ENOUGH_VULTURE::FA_DECO_CONDITION_NOT_ENOUGH_VULTURE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughVulture) {}


std::string FA_DECO_CONDITION_NOT_ENOUGH_VULTURE::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_VULTURE";
}

bool FA_DECO_CONDITION_NOT_ENOUGH_VULTURE::IsThereNotEnoughVulture(void *data)
{
    Data* pData = (Data*)data;
    
    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 75 or unusedSupply < 4)
    {
        return false;
    }

    auto units = BWAPI::Broodwar->self()->getUnits();
    int timePeriod = BWAPI::Broodwar->elapsedTime();
    int vultures = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Vulture, units);
    if (timePeriod <= EARLY_GAME and vultures < 3)
        return true;
    else if (timePeriod <= MID_GAME and vultures < 6)
        return true;
    else if (vultures < 4)
        return true;
    else
        return false;

    return false;
}
