#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BC_ACTION_USE_ABILITY_YAMATOGUN : public BT_ACTION {
public:
    BC_ACTION_USE_ABILITY_YAMATOGUN(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityYamatogun(void* data);
};
//----------