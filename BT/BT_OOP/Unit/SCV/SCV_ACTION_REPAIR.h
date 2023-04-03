#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SCV_ACTION_REPAIR : public BT_ACTION {
public:
    SCV_ACTION_REPAIR(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionRepair(void* data);
};
//----------