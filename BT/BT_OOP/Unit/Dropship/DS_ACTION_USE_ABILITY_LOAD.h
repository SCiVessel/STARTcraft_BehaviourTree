#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class DS_ACTION_USE_ABILITY_LOAD : public BT_ACTION {
public:
    DS_ACTION_USE_ABILITY_LOAD(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityLoad(void* data);
};
//----------