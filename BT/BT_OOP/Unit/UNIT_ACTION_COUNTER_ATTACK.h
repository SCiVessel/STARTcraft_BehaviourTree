#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class UNIT_ACTION_COUNTER_ATTACK: public BT_ACTION {
public:
    UNIT_ACTION_COUNTER_ATTACK(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State CounterAttack(void* data);
};
//----------