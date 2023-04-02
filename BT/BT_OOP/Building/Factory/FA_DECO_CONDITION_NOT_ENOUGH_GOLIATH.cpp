#include "FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH::FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughGoliath) {}


std::string FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_GOLIATH";
}

bool FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH::IsThereNotEnoughGoliath(void* data)
{
    Data* pData = (Data*)data;
    auto units = BWAPI::Broodwar->self()->getUnits();

    int Armories = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Armory, units);
    if (Armories < 1)
    {
        return false;
    }

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 100 or BWAPI::Broodwar->self()->gas() < 50 or unusedSupply < 4)
    {
        return false;
    }

    int goliaths = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Goliath, units);
    if (goliaths < 4)
        return true;
    else
    {
        auto enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
        int airEnemies = 0;
        for (auto eu : enemyUnits)
            if (eu->isFlying())
                airEnemies++;
        
        if (airEnemies / 3 > goliaths)
            return true;
        else
            return false;
    }

    return false;
}
