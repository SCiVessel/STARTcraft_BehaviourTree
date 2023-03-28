#include "BA_DECO_CONDITION_NOT_ENOUGH_GHOST.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BA_DECO_CONDITION_NOT_ENOUGH_GHOST::BA_DECO_CONDITION_NOT_ENOUGH_GHOST(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, IsThereNotEnoughGhost) {}


std::string BA_DECO_CONDITION_NOT_ENOUGH_GHOST::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_GHOST";
}

bool BA_DECO_CONDITION_NOT_ENOUGH_GHOST::IsThereNotEnoughGhost(void* data)
{
    Data* pData = (Data*)data;

    int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();
    if (BWAPI::Broodwar->self()->minerals() < 25 or BWAPI::Broodwar->self()->gas() < 75 or unusedSupply < 2)
    {
        return false;
    }

    auto enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
    int enemyRace = -1;
    for (auto eu : enemyUnits)
    {
        enemyRace = eu->getType().getRace();
        if (enemyRace != -1)
            break;
    }

    auto units = BWAPI::Broodwar->self()->getUnits();
    int ghosts = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Ghost, units);

    if (enemyRace == 0) // Zerg
    {
        if (ghosts >= 2)
            return false;
        return true;
    }
    else
    {
        if (ghosts > 6)
            return false;
        int largeEnemy = 0;
        for (auto eu : enemyUnits)
            if (eu->getType().supplyRequired() / 2 >= 4)
                largeEnemy++;
        if (ghosts < largeEnemy / 2)
            return true;
        return false;
    }

    return false;
}
