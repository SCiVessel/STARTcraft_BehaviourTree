#include "UNIT_ACTION_RETRIBUTIVE_ATTACK.h"
#include "Tools.h"
#include "Data.h"

UNIT_ACTION_RETRIBUTIVE_ATTACK::UNIT_ACTION_RETRIBUTIVE_ATTACK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State UNIT_ACTION_RETRIBUTIVE_ATTACK::Evaluate(void* data)
{
    return ReturnState(RetributiveAttack(data));
}

std::string UNIT_ACTION_RETRIBUTIVE_ATTACK::GetDescription()
{
    return "RETRIBUTIVE ATTACK";
}


BT_NODE::State UNIT_ACTION_RETRIBUTIVE_ATTACK::RetributiveAttack(void* data)
{
    Data* pData = (Data*)data;

    // F2
    std::vector<BWAPI::Unit> F2;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit can be selected with F2
        if (unit->canAttack() && unit->getType() != BWAPI::UnitTypes::Terran_SCV)
        {
            F2.push_back(unit);
        }
    }

    // Enemy currently attacking
    BWAPI::Unitset enemyUnitsAttacking;
    for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits())
    {
        if (enemy->exists() && enemy->isAttacking() && enemy->isDetected())
        {
            enemyUnitsAttacking.insert(enemy);
            break;
        }
    }

    // F2 & ATTACK
    for (auto& unit : F2)
    {
        if (unit && !unit->isAttacking() && !enemyUnitsAttacking.empty())
        {
            if (unit->getDistance(*begin(enemyUnitsAttacking)) <= RETALIATE_DISTANCE)
            {
                Tools::SmartRightClick(unit, *begin(enemyUnitsAttacking));
            }
        }
    }
    
    /*BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None)
        return BT_NODE::FAILURE;
    else return BT_NODE::SUCCESS;*/

    return BT_NODE::SUCCESS;
}