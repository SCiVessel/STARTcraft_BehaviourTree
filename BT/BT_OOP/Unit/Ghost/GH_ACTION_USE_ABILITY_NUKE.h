#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class GH_ACTION_USE_ABILITY_NUKE : public BT_ACTION {
public:
    GH_ACTION_USE_ABILITY_NUKE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityNuke(void* data);
};
//----------