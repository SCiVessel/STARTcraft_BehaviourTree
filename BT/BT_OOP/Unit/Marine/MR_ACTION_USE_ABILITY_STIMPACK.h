#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class MR_ACTION_USE_ABILITY_STIMPACK : public BT_ACTION {
public:
    MR_ACTION_USE_ABILITY_STIMPACK(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityStimpack(void* data);
};
//----------