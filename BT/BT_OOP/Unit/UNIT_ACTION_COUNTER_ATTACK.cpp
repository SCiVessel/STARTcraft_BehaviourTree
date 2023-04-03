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
    BWAPI::Unitset F2;
    BWAPI::Unitset woundedF2;
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

    bool isCounterAttack = (BWAPI::Broodwar->self()->supplyUsed() >= COUNTER_ATTACK_SUPPLY || pData->enemyMainDestroyed == true) ? true : false;

    // F2 & ATTACK
    for (auto& unit : F2)
    {
        if ((!unit->isAttacking()) || (unit->getTarget() == nullptr) || (unit->isIdle()))
        {
            if (isCounterAttack)
            {
                unit->attack(pData->enemySpawnLocation);
            }
            else if (pData->at_war == false)
            {
                unit->move(BWAPI::Position(pData->rallyPoint));
            }   
        }

        if (unit->getInitialHitPoints() > unit->getHitPoints())
        {
            if (unit->getType().isOrganic())
            {
                woundedF2.insert(unit);
            }
        }
    }

    for (auto& unit : Casters)
    {
        if ((unit->getTarget() == nullptr) || (unit->isIdle()))
        {
            if (isCounterAttack)
            {
                if (!woundedF2.empty())
                {
                    Tools::SmartRightClick(unit, (Tools::GetClosestUnitTo(unit, woundedF2)));
                }
                else
                {
                    Tools::SmartRightClick(unit, (Tools::GetClosestUnitTo(unit, F2)));
                }

            }
            else if (pData->at_war == false)
            {
                if (unit->getClosestUnit(BWAPI::Filter::IsOwned && BWAPI::Filter::IsBuilding) == nullptr)
                {
                    unit->move(BWAPI::Position(pData->rallyPoint));
                }
            }
        }
    }

    /*BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None)
        return BT_NODE::FAILURE;
    else return BT_NODE::SUCCESS;*/

    return BT_NODE::SUCCESS;
}