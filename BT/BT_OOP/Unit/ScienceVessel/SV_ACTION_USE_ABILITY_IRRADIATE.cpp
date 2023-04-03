#include "SV_ACTION_USE_ABILITY_IRRADIATE.h"
#include "Tools.h"
#include "Data.h"

SV_ACTION_USE_ABILITY_IRRADIATE::SV_ACTION_USE_ABILITY_IRRADIATE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SV_ACTION_USE_ABILITY_IRRADIATE::Evaluate(void* data)
{
    return ReturnState(useAbilityIrradiate(data));
}

std::string SV_ACTION_USE_ABILITY_IRRADIATE::GetDescription()
{
    return "ACTION USE ABILITY IRRADIATE";
}

BT_NODE::State SV_ACTION_USE_ABILITY_IRRADIATE::useAbilityIrradiate(void* data)
{
    Data* pData = (Data*)data;

    int energy = 75;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Vessel && unit->isCompleted())
        {
            auto enemies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 288, BWAPI::Filter::IsEnemy && BWAPI::Filter::IsFlyer);
            if (unit->getEnergy() >= energy && enemies.size())
            {
                BWAPI::Unit target;
                int supply = -1;
                for (auto e : enemies)
                {
                    int supplyE = e->getType().supplyRequired();
                    if (supplyE > supply)
                    {
                        supply = supplyE;
                    }
                }
                if (supply > 0)
                {
                    for (auto e : enemies)
                    {
                        if (e->getType().supplyRequired() == supply)
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

                if (unit->canUseTech(BWAPI::TechTypes::Irradiate, target))
                {
                    unit->useTech(BWAPI::TechTypes::Irradiate, target);
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