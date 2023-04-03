#include "DS_ACTION_USE_ABILITY_LOAD.h"
#include "Tools.h"
#include "Data.h"

DS_ACTION_USE_ABILITY_LOAD::DS_ACTION_USE_ABILITY_LOAD(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State DS_ACTION_USE_ABILITY_LOAD::Evaluate(void* data)
{
    return ReturnState(useAbilityLoad(data));
}

std::string DS_ACTION_USE_ABILITY_LOAD::GetDescription()
{
    return "ACTION USE ABILITY LOAD";
}

BT_NODE::State DS_ACTION_USE_ABILITY_LOAD::useAbilityLoad(void* data)
{
    return BT_NODE::FAILURE;
}
