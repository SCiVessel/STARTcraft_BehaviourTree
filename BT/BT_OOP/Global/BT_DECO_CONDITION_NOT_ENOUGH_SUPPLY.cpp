#include "BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY::BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughSupply) {}


std::string BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_SUPPLY";
}

bool BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY::IsThereNotEnoughSupply(void *data)
{
    Data* pData = (Data*)data;
    
    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 100) //100
    {
        return false;
    }

    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

    if (Tools::GetTotalSupply(false) >= 400)
    {
        return false;
    }

    // If we have a sufficient amount of supply, we don't need to do anything
    if (unusedSupply < pData->thresholdSupply)
    {
        return true;
    }
    else if (unusedSupply <= 0) {
        return true;
    }
    else
    {
        return false;
    }
}
