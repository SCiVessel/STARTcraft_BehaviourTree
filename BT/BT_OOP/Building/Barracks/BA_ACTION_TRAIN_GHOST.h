#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BA_ACTION_TRAIN_GHOST : public BT_ACTION {
public:
    BA_ACTION_TRAIN_GHOST(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State TrainGhost(void* data);
};
//----------