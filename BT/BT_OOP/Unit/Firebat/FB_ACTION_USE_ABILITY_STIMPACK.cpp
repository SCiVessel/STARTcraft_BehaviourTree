#include "FB_ACTION_USE_ABILITY_STIMPACK.h"
#include "Tools.h"
#include "Data.h"

FB_ACTION_USE_ABILITY_STIMPACK::FB_ACTION_USE_ABILITY_STIMPACK(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State FB_ACTION_USE_ABILITY_STIMPACK::Evaluate(void* data)
{
    return ReturnState(useAbilityStimpack(data));
}

std::string FB_ACTION_USE_ABILITY_STIMPACK::GetDescription()
{
    return "ACTION USE ABILITY STIMPACK";
}

BT_NODE::State FB_ACTION_USE_ABILITY_STIMPACK::useAbilityStimpack(void* data)
{
    Data* pData = (Data*)data;

    int hp = 10;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Firebat && unit->isCompleted())
        {
            int hasEnemyInRange = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 96, BWAPI::Filter::IsEnemy).size();
            if (unit->getHitPoints() >= hp && unit->canUseTech(BWAPI::TechTypes::Stim_Packs) && hasEnemyInRange)
            {
                executed = true;
                unit->useTech(BWAPI::TechTypes::Stim_Packs);
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