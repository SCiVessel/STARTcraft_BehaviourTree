#include "DS_ACTION_USE_ABILITY_UNLOAD.h"
#include "Tools.h"
#include "Data.h"

DS_ACTION_USE_ABILITY_UNLOAD::DS_ACTION_USE_ABILITY_UNLOAD(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State DS_ACTION_USE_ABILITY_UNLOAD::Evaluate(void* data)
{
    return ReturnState(useAbilityUnload(data));
}

std::string DS_ACTION_USE_ABILITY_UNLOAD::GetDescription()
{
    return "ACTION USE ABILITY UNLOAD";
}

BT_NODE::State DS_ACTION_USE_ABILITY_UNLOAD::useAbilityUnload(void* data)
{
    return BT_NODE::FAILURE;
}
