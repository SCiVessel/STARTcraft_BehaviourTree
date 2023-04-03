#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class PL_ACTION_RESEARCH_YAMATOGUN : public BT_ACTION {
public:
    PL_ACTION_RESEARCH_YAMATOGUN(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchYamatogun(void* data);
};
//----------