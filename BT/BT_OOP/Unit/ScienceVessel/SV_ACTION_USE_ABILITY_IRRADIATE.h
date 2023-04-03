#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SV_ACTION_USE_ABILITY_IRRADIATE : public BT_ACTION {
public:
    SV_ACTION_USE_ABILITY_IRRADIATE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityIrradiate(void* data);
};
//----------