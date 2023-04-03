#include "GH_ACTION_USE_ABILITY_LOCKDOWN.h"
#include "Tools.h"
#include "Data.h"

GH_ACTION_USE_ABILITY_LOCKDOWN::GH_ACTION_USE_ABILITY_LOCKDOWN(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State GH_ACTION_USE_ABILITY_LOCKDOWN::Evaluate(void* data)
{
    return ReturnState(useAbilityLockdown(data));
}

std::string GH_ACTION_USE_ABILITY_LOCKDOWN::GetDescription()
{
    return "ACTION USE ABILITY LOCKDOWN";
}

BT_NODE::State GH_ACTION_USE_ABILITY_LOCKDOWN::useAbilityLockdown(void* data)
{
    Data* pData = (Data*)data;

    int energy = 100;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        bool hasUnitToExecute = false;
        if (unit->getType() == BWAPI::UnitTypes::Terran_Ghost && unit->isCompleted())
        {
            auto enemies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 256, BWAPI::Filter::IsEnemy && BWAPI::Filter::IsMechanical);
            if (unit->getEnergy() >= energy && enemies.size())
            {
                BWAPI::Unit target;
                int supply = -1;
                for (auto e : enemies)
                {
                    int supplyE = e->getType().supplyRequired();
                    if (supplyE > supply && !e->isLockedDown())
                    {
                        supply = supplyE;
                    }
                }
                if (supply > 0)
                {
                    for (auto e : enemies)
                    {
                        if (e->getType().supplyRequired() == supply && !e->isLockedDown())
                        {
                            target = e;
                            hasUnitToExecute = true;
                            break;
                        }
                    }
                }

                if (!hasUnitToExecute)
                {
                    return BT_NODE::FAILURE;
                }
                if (unit->canUseTech(BWAPI::TechTypes::Lockdown, target))
                {
                    unit->useTech(BWAPI::TechTypes::Lockdown, target);
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