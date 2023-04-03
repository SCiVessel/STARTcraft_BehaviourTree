#include "GH_ACTION_USE_ABILITY_CLOAK.h"
#include "Tools.h"
#include "Data.h"

GH_ACTION_USE_ABILITY_CLOAK::GH_ACTION_USE_ABILITY_CLOAK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State GH_ACTION_USE_ABILITY_CLOAK::Evaluate(void* data)
{
    return ReturnState(useAbilityCloak(data));
}

std::string GH_ACTION_USE_ABILITY_CLOAK::GetDescription()
{
    return "ACTION USE ABILITY CLOAK";
}

BT_NODE::State GH_ACTION_USE_ABILITY_CLOAK::useAbilityCloak(void* data)
{
    Data* pData = (Data*)data;

    float energy = 25.93f;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Ghost && unit->isCompleted())
        {
            int hasEnemyInRange = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 288, BWAPI::Filter::IsEnemy).size();
            if (unit->getEnergy() >= energy && unit->canUseTech(BWAPI::TechTypes::Personnel_Cloaking) && hasEnemyInRange)
            {
                executed = true;
                unit->useTech(BWAPI::TechTypes::Personnel_Cloaking);
            }
        }
    }

    if (!executed)
    {
        return BT_NODE::FAILURE;
    }
    else
    {
        return BT_NODE::SUCCESS;
    }
}