#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SP_ACTION_TRAIN_BATTLECRUISER : public BT_ACTION {
public:
    SP_ACTION_TRAIN_BATTLECRUISER(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State TrainBattlecruiser(void* data);
};
//----------