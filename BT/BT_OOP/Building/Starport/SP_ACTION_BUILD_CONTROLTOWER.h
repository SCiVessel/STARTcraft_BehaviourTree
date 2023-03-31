#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SP_ACTION_BUILD_CONTROLTOWER : public BT_ACTION {
public:
    SP_ACTION_BUILD_CONTROLTOWER(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State buildControlTower(void* data);
};
//----------