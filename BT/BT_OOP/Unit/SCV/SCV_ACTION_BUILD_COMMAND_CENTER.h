#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SCV_ACTION_BUILD_COMMAND_CENTER : public BT_ACTION {
public:
    SCV_ACTION_BUILD_COMMAND_CENTER(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State BuildCommandcenter(void* data);
};
//----------