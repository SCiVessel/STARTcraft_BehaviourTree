#include "WR_ACTION_USE_ABILITY_UNCLOAK.h"
#include "Tools.h"
#include "Data.h"

WR_ACTION_USE_ABILITY_UNCLOAK::WR_ACTION_USE_ABILITY_UNCLOAK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State WR_ACTION_USE_ABILITY_UNCLOAK::Evaluate(void* data)
{
    return ReturnState(useAbilityUncloak(data));
}

std::string WR_ACTION_USE_ABILITY_UNCLOAK::GetDescription()
{
    return "ACTION USE ABILITY UNCLOAK";
}

BT_NODE::State WR_ACTION_USE_ABILITY_UNCLOAK::useAbilityUncloak(void* data)
{
    Data* pData = (Data*)data;

    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Wraith && unit->isCompleted())
        {
            int hasEnemyInRange = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 192, BWAPI::Filter::IsEnemy).size();
            if (unit->isCloaked() && unit->canUseTech(BWAPI::TechTypes::Cloaking_Field) && !hasEnemyInRange)
            {
                unit->useTech(BWAPI::TechTypes::Cloaking_Field);
                executed = true;
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