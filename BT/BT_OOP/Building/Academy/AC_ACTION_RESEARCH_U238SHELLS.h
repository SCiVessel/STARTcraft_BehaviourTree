#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class AC_ACTION_RESEARCH_U238SHELLS : public BT_ACTION {
public:
    AC_ACTION_RESEARCH_U238SHELLS(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchU238shells(void* data);
};
//----------