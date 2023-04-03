#include "GH_ACTION_USE_ABILITY_UNCLOAK.h"
#include "Tools.h"
#include "Data.h"

GH_ACTION_USE_ABILITY_UNCLOAK::GH_ACTION_USE_ABILITY_UNCLOAK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State GH_ACTION_USE_ABILITY_UNCLOAK::Evaluate(void* data)
{
    return ReturnState(useAbilityUncloak(data));
}

std::string GH_ACTION_USE_ABILITY_UNCLOAK::GetDescription()
{
    return "ACTION USE ABILITY UNCLOAK";
}

BT_NODE::State GH_ACTION_USE_ABILITY_UNCLOAK::useAbilityUncloak(void* data)
{
    Data* pData = (Data*)data;

    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Ghost && unit->isCompleted())
        {
            int hasEnemyInRange = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 288, BWAPI::Filter::IsEnemy).size();
            if (unit->isCloaked() && unit->canUseTech(BWAPI::TechTypes::Personnel_Cloaking) && !hasEnemyInRange)
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