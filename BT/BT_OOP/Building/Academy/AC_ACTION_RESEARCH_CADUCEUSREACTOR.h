#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class AC_ACTION_RESEARCH_CADUCEUSREACTOR : public BT_ACTION {
public:
    AC_ACTION_RESEARCH_CADUCEUSREACTOR(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchCaduceusreactor(void* data);
};
//----------