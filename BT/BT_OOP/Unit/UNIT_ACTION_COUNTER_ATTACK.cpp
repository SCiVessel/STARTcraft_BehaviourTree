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

    bool isCounterAttack = BWAPI::Broodwar->self()->supplyUsed() >= COUNTER_ATTACK_SUPPLY ? true : false;

    // F2 & ATTACK
    for (auto& unit : F2)
    {
        if ((!unit->isAttacking()) || (unit->getTarget() == nullptr) || (unit->isIdle()))
        {
            if (isCounterAttack)
            {
                unit->attack(pData->enemySpawnLocation);
            }
            else
            {
                unit->attack(BWAPI::Position(pData->rallyPoint));
            }   
        }
    }

    for (auto& caster : Casters)
    {
        if (caster->getType() == BWAPI::UnitTypes::Terran_Medic)
        {
            BWAPI::Unitset bioUnits = caster->getUnitsInRadius(128, BWAPI::Filter::IsOwned && BWAPI::Filter::IsOrganic);
            for (auto& wounded : bioUnits)
            {
                if (wounded->getInitialHitPoints() > wounded->getHitPoints())
                {
                    caster->useTech(BWAPI::TechTypes::Healing, wounded);
                    break;
                }
            }
        }

        if ((caster->getTarget() == nullptr) || (caster->isIdle()))
        {
            BWAPI::Unit followMe = Tools::GetClosestUnitTo(caster, F2);
            if (followMe != nullptr)
            {
                caster->follow(followMe);
            }
        }
    }
    /*BWAPI::Error error = BWAPI::Broodwar->getLastError();
    if (error != BWAPI::Errors::None)
        return BT_NODE::FAILURE;
    else return BT_NODE::SUCCESS;*/

    return BT_NODE::SUCCESS;
}