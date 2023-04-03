#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class CO_ACTION_RESEARCH_PERSONALCLOAKING : public BT_ACTION {
public:
    CO_ACTION_RESEARCH_PERSONALCLOAKING(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchPersonalcloaking(void* data);
};
//----------