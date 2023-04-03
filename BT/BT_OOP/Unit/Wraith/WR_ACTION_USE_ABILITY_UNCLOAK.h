#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class WR_ACTION_USE_ABILITY_UNCLOAK : public BT_ACTION {
public:
    WR_ACTION_USE_ABILITY_UNCLOAK(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityUncloak(void* data);

    static int startWarTime;
    static int outOfWarTime;
};
//----------