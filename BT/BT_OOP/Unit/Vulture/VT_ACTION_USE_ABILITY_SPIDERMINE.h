#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class VT_ACTION_USE_ABILITY_SPIDERMINE : public BT_ACTION {
public:
    VT_ACTION_USE_ABILITY_SPIDERMINE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilitySpidermine(void* data);
};
//----------