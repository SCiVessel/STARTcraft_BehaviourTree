#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class CS_ACTION_USE_ABILITY_SCANNERSWEEP : public BT_ACTION {
public:
    CS_ACTION_USE_ABILITY_SCANNERSWEEP(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State useAbilityScannerSweep(void* data);
};
//----------