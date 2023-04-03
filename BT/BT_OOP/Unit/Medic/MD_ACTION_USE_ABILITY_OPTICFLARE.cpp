#include "MD_ACTION_USE_ABILITY_OPTICFLARE.h"
#include "Tools.h"
#include "Data.h"

MD_ACTION_USE_ABILITY_OPTICFLARE::MD_ACTION_USE_ABILITY_OPTICFLARE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State MD_ACTION_USE_ABILITY_OPTICFLARE::Evaluate(void* data)
{
    return ReturnState(useAbilityOpticflare(data));
}

std::string MD_ACTION_USE_ABILITY_OPTICFLARE::GetDescription()
{
    return "ACTION USE ABILITY OPTICFLARE";
}

BT_NODE::State MD_ACTION_USE_ABILITY_OPTICFLARE::useAbilityOpticflare(void* data)
{
    return BT_NODE::FAILURE;
}