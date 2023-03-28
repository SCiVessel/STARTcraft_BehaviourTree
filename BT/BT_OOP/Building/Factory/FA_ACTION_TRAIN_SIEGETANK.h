#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class FA_ACTION_TRAIN_SIEGETANK : public BT_ACTION {
public:
    FA_ACTION_TRAIN_SIEGETANK(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State TrainSiegetank(void* data);
};
//----------