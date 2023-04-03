#include "GH_ACTION_USE_ABILITY_NUKE.h"
#include "Tools.h"
#include "Data.h"

GH_ACTION_USE_ABILITY_NUKE::GH_ACTION_USE_ABILITY_NUKE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State GH_ACTION_USE_ABILITY_NUKE::Evaluate(void* data)
{
    return ReturnState(useAbilityNuke(data));
}

std::string GH_ACTION_USE_ABILITY_NUKE::GetDescription()
{
    return "ACTION USE ABILITY NUKE";
}

BT_NODE::State GH_ACTION_USE_ABILITY_NUKE::useAbilityNuke(void* data)
{
    return BT_NODE::FAILURE;
}