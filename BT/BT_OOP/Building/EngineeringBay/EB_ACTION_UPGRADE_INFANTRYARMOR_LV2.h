#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class EB_ACTION_UPGRADE_INFANTRYARMOR_LV2 : public BT_ACTION {
public:
    EB_ACTION_UPGRADE_INFANTRYARMOR_LV2(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchInfantryarmorlv2(void* data);
};
//----------