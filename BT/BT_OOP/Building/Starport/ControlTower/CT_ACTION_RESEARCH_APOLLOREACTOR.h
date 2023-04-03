#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class CT_ACTION_RESEARCH_APOLLOREACTOR : public BT_ACTION {
public:
    CT_ACTION_RESEARCH_APOLLOREACTOR(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchApolloreactor(void* data);
};
//----------