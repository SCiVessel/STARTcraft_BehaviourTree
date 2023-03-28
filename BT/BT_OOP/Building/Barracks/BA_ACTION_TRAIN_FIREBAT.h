#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BA_ACTION_TRAIN_FIREBAT : public BT_ACTION {
public:
    BA_ACTION_TRAIN_FIREBAT(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State TrainFirebat(void* data);
};
//----------