#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SF_ACTION_RESEARCH_EMPSHOCKWAVE : public BT_ACTION {
public:
    SF_ACTION_RESEARCH_EMPSHOCKWAVE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchEmpshockwave(void* data);
};
//----------