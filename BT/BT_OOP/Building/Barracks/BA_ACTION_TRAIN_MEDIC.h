#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class BA_ACTION_TRAIN_MEDIC : public BT_ACTION {
public:
    BA_ACTION_TRAIN_MEDIC(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State TrainMedic(void* data);
};
//----------