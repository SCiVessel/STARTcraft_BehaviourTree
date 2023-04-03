#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class MS_ACTION_RESEARCH_SPIDERMINE : public BT_ACTION {
public:
    MS_ACTION_RESEARCH_SPIDERMINE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchSpidermine(void* data);
};
//----------