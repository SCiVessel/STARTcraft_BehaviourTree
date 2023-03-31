#include "UNIT_ACTION_COUNTER_ATTACK.h"
#include "Tools.h"
#include "Data.h"

#include "BWEM.h"

UNIT_ACTION_COUNTER_ATTACK::UNIT_ACTION_COUNTER_ATTACK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State UNIT_ACTION_COUNTER_ATTACK::Evaluate(void* data)
{
    return ReturnState(CounterAttack(data));
}

std::string UNIT_ACTION_COUNTER_ATTACK::GetDescription()
{
    return "COUNTER ATTACK";
}


BT_NODE::State UNIT_ACTION_COUNTER_ATTACK::CounterAttack(void* data)
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

    bool isCounterAttack = BWAPI::Broodwar->self()->supplyUsed() >= COUNTER_ATTACK_SUPPLY ? true : false;

    // F2 & ATTACK
    for (auto& unit : F2)
    {
        if (unit && unit->isIdle())
        {
            if (isCounterAttack)
            {
                unit->attack(pData->enemySpawnLocation);
            }
            else
            {
                unit->move(BWAPI::Position(pData->rallyPoint));
            }
            
        }
    }
    
    /*BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None)
        return BT_NODE::FAILURE;
    else return BT_NODE::SUCCESS;*/

    return BT_NODE::SUCCESS;
}