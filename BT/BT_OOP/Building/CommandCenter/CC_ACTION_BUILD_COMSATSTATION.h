#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class CC_ACTION_BUILD_COMSATSTATION : public BT_ACTION {
public:
    CC_ACTION_BUILD_COMSATSTATION(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State buildComsatStation(void* data);
};
//----------