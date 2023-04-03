#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class UNIT_ACTION_SEARCHSIDES : public BT_ACTION {
public:
    UNIT_ACTION_SEARCHSIDES(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionSearchsides(void* data);
};
//----------