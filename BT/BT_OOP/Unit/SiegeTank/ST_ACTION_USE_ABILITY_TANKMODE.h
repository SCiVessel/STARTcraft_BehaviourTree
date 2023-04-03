#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class ST_ACTION_USE_ABILITY_TANKMODE : public BT_ACTION {
public:
    ST_ACTION_USE_ABILITY_TANKMODE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityTankmode(void* data);

    static int startWarTime;
    static int outOfWarTime;
};
//----------