#include "BC_ACTION_USE_ABILITY_YAMATOGUN.h"
#include "Tools.h"
#include "Data.h"


BC_ACTION_USE_ABILITY_YAMATOGUN::BC_ACTION_USE_ABILITY_YAMATOGUN(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State BC_ACTION_USE_ABILITY_YAMATOGUN::Evaluate(void* data)
{
    return ReturnState(useAbilityYamatogun(data));
}

std::string BC_ACTION_USE_ABILITY_YAMATOGUN::GetDescription()
{
    return "ACTION USE ABILITY YAMATOGUN";
}

BT_NODE::State BC_ACTION_USE_ABILITY_YAMATOGUN::useAbilityYamatogun(void* data)
{
    Data* pData = (Data*)data;

    int energy = 150;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        bool hasUnitToExecute = false;
        if (unit->getType() == BWAPI::UnitTypes::Terran_Battlecruiser && unit->isCompleted())
        {
            auto enemies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 320, BWAPI::Filter::IsEnemy);
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
                        if (e->getType().supplyRequired())
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
                if (unit->canUseTech(BWAPI::TechTypes::Yamato_Gun, target))
                {
                    unit->useTech(BWAPI::TechTypes::Yamato_Gun, target);
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
