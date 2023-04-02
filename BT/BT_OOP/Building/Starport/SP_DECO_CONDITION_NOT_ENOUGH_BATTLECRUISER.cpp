#include "SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER::SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughBattlecruiser) {}


std::string SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER";
}

bool SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER::IsThereNotEnoughBattlecruiser(void* data)
{
    Data* pData = (Data*)data;

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() > 2400 && BWAPI::Broodwar->self()->gas() > 1800 && unusedSupply >= 12)
    {
        return true;
    }

    return false;
}
