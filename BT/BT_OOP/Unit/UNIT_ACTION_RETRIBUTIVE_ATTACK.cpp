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
    BWAPI::Unitset F2;
    BWAPI::Unitset Casters;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit can be selected with F2
        if ((unit->getType() == BWAPI::UnitTypes::Terran_Science_Vessel))
        {
            Casters.insert(unit);
        }
        else if ((unit->canAttack() && (unit->getType() != BWAPI::UnitTypes::Terran_SCV)) || (unit->getType() == BWAPI::UnitTypes::Terran_Medic))
        {
            F2.insert(unit);
        }
    }

    if (F2.size() <= 3)
    {
        for (auto& unit : BWAPI::Broodwar->self()->getUnits())
        {
            if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
            {
                F2.insert(unit);
                for (auto& check : pData->unitsFarmingMinerals)
                {
                    if (check.contains(unit))
                    {
                        check.erase(unit);
                        break;
                    }
                }
                for (auto& check : pData->unitsFarmingGeysers)
                {
                    if (check.contains(unit))
                    {
                        check.erase(unit);
                        break;
                    }
                }

                if (F2.size() >= 8)
                {
                    break;
                }
            }
        }
    }

    // Enemy currently attacking
    BWAPI::Unitset enemiesAttacking;
    BWAPI::Unitset enemiesHealing;

    for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits())
    {
        if (enemy->isVisible() || enemy->isDetected())
        {
            if ((enemy->getType() == BWAPI::UnitTypes::Terran_Medic) || enemy->isRepairing())
            {
                enemiesHealing.insert(enemy);
            }
            else
            {
                enemiesAttacking.insert(enemy);
            }
        }
    }

    // F2 & ATTACK
    for (auto& unit : F2)
    {
        if ((!unit->isAttacking()) || (unit->getTarget() == nullptr) || (unit->isIdle()))
        {
            BWAPI::Unit closetEnemy = unit->getClosestUnit(BWAPI::Filter::IsEnemy);
            if (closetEnemy == nullptr)
            {
                break;
            }

            if ((unit->getDistance(closetEnemy) <= pData->maxAggroDistance) || unit->isUnderAttack())
            {
                if (!enemiesHealing.empty())
                {
                    for (auto& enemyHealer : enemiesHealing)
                    {
                        if (unit->isInWeaponRange(enemyHealer))
                        {
                            Tools::SmartRightClick(unit, enemyHealer);
                        }
                    }

                }
                else if (!enemiesAttacking.empty())
                {
                    bool flag = false;
                    for (auto& enemyAttacker : enemiesAttacking)
                    {
                        if (unit->isInWeaponRange(enemyAttacker))
                        {
                            Tools::SmartRightClick(unit, enemyAttacker);
                            flag = true;
                            break;
                        }
                    }
                    
                    if (flag == false)
                    {
                        Tools::SmartRightClick(unit, closetEnemy);
                    }
                }
            }
        }
    }

    for (auto& caster : Casters)
    {
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