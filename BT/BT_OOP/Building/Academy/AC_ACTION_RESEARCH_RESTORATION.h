#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class AC_ACTION_RESEARCH_RESTORATION : public BT_ACTION {
public:
    AC_ACTION_RESEARCH_RESTORATION(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchRestoration(void* data);
};
//----------