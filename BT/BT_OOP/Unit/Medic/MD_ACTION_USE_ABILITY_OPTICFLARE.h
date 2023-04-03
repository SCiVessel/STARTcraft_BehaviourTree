#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class MD_ACTION_USE_ABILITY_OPTICFLARE : public BT_ACTION {
public:
    MD_ACTION_USE_ABILITY_OPTICFLARE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityOpticflare(void* data);
};
//----------