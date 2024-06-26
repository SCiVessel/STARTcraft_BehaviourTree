#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BA_ACTION_TRAIN_MARINE: public BT_ACTION {
public:
    BA_ACTION_TRAIN_MARINE(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State TrainMarine(void* data);
};
//----------