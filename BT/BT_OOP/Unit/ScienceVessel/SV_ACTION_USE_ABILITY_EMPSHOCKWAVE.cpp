#include "SV_ACTION_USE_ABILITY_EMPSHOCKWAVE.h"
#include "Tools.h"
#include "Data.h"

SV_ACTION_USE_ABILITY_EMPSHOCKWAVE::SV_ACTION_USE_ABILITY_EMPSHOCKWAVE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SV_ACTION_USE_ABILITY_EMPSHOCKWAVE::Evaluate(void* data)
{
    return ReturnState(useAbilityEmpshockwave(data));
}

std::string SV_ACTION_USE_ABILITY_EMPSHOCKWAVE::GetDescription()
{
    return "ACTION USE ABILITY EMPSHOCKWAVE";
}

BT_NODE::State SV_ACTION_USE_ABILITY_EMPSHOCKWAVE::useAbilityEmpshockwave(void* data)
{
    Data* pData = (Data*)data;

    int energy = 100;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Vessel && unit->isCompleted())
        {
            auto enemies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 256, BWAPI::Filter::IsEnemy && BWAPI::Filter::MaxEnergy);
            if (unit->getEnergy() >= energy && enemies.size())
            {
                BWAPI::Unit target;
                float value = -1.0f;
                for (auto e : enemies)
                {
                    float valueE = e->getType().mineralPrice() + e->getType().gasPrice() * 1.2f;
                    if (valueE > value)
                    {
                        value = valueE;
                    }
                }
                if (value > 0)
                {
                    for (auto e : enemies)
                    {
                        if (e->getType().supplyRequired() == value)
                        {
                            target = e;
                            break;
                        }
                    }
                }
                else
                {
                    return BT_NODE::FAILURE;
                }

                if (unit->canUseTech(BWAPI::TechTypes::EMP_Shockwave, target))
                {
                    unit->useTech(BWAPI::TechTypes::EMP_Shockwave, target);
                    executed = true;
                }
            }
        }
    }

    if (executed)
    {
        return BT_NODE::SUCCESS;
    }
    else
    {
        return BT_NODE::FAILURE;
    }
}