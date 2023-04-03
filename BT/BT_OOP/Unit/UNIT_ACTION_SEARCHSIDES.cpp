#include "UNIT_ACTION_SEARCHSIDES.h"
#include "Tools.h"
#include "Data.h"

UNIT_ACTION_SEARCHSIDES::UNIT_ACTION_SEARCHSIDES(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State UNIT_ACTION_SEARCHSIDES::Evaluate(void* data)
{
    return ReturnState(actionSearchsides(data));
}

std::string UNIT_ACTION_SEARCHSIDES::GetDescription()
{
    return "ACTION SEARCH SIDES";
}

BT_NODE::State UNIT_ACTION_SEARCHSIDES::actionSearchsides(void* data)
{
    Data* pData = (Data*)data;


    if (pData->enemyMainDestroyed == false)
    {
        return BT_NODE::FAILURE;
    }


    BWAPI::Unitset F2;
    BWAPI::Unitset Casters;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit can be selected with F2
        if ((unit->getType() == BWAPI::UnitTypes::Terran_Science_Vessel) || (unit->getType() == BWAPI::UnitTypes::Terran_Medic))
        {
            Casters.insert(unit);
        }
        else if (unit->canAttack() && (unit->getType() != BWAPI::UnitTypes::Terran_SCV))
        {
            F2.insert(unit);
        }
    }

    BWAPI::Unitset visibleEnemy = BWAPI::Broodwar->enemy()->getUnits();
    for (auto& theLastOfUs : visibleEnemy)
    {
        F2.attack(theLastOfUs);
        Casters.attack(theLastOfUs);
        return BT_NODE::SUCCESS;
    }
      
    for (size_t i = pData->attackBaseLocation; i < pData->tilesOfExpansions.size(); i++)
    {
        if (BWAPI::Broodwar->isVisible(pData->tilesOfExpansions[pData->attackBaseLocation]) == false)
        {
            F2.attack(BWAPI::Position(pData->tilesOfExpansions[pData->attackBaseLocation]));
            Casters.attack(BWAPI::Position(pData->tilesOfExpansions[pData->attackBaseLocation]));

            pData->attackBaseLocation = i + 1;
            return BT_NODE::SUCCESS;
        }
    }
    pData->attackBaseLocation = 0;
        

    return BT_NODE::FAILURE;
}