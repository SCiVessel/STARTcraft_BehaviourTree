#include "MD_ACTION_USE_ABILITY_HEAL.h"
#include "Tools.h"
#include "Data.h"

MD_ACTION_USE_ABILITY_HEAL::MD_ACTION_USE_ABILITY_HEAL(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State MD_ACTION_USE_ABILITY_HEAL::Evaluate(void* data)
{
    return ReturnState(useAbilityHeal(data));
}

std::string MD_ACTION_USE_ABILITY_HEAL::GetDescription()
{
    return "ACTION USE ABILITY HEAL";
}

BT_NODE::State MD_ACTION_USE_ABILITY_HEAL::useAbilityHeal(void* data)
{
    return BT_NODE::SUCCESS;
}