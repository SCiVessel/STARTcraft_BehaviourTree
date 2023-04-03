#include "WR_ACTION_USE_ABILITY_CLOAK.h"
#include "Tools.h"
#include "Data.h"

WR_ACTION_USE_ABILITY_CLOAK::WR_ACTION_USE_ABILITY_CLOAK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State WR_ACTION_USE_ABILITY_CLOAK::Evaluate(void* data)
{
    return ReturnState(useAbilityCloak(data));
}

std::string WR_ACTION_USE_ABILITY_CLOAK::GetDescription()
{
    return "ACTION USE ABILITY CLOAK";
}

BT_NODE::State WR_ACTION_USE_ABILITY_CLOAK::useAbilityCloak(void* data)
{
    Data* pData = (Data*)data;

    float energy = 25.186f;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Wraith && unit->isCompleted())
        {
            int hasEnemyInRange = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 192, BWAPI::Filter::IsEnemy).size();
            if (unit->getEnergy() >= energy && unit->canUseTech(BWAPI::TechTypes::Cloaking_Field) && hasEnemyInRange)
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