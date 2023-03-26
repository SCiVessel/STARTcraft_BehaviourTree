#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS : public BT_ACTION {
public:
    SCV_ACTION_SEND_IDLE_WORKER_TO_GEYSERS(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State SendIdleWorkerToGeysers(void* data);
};
//----------