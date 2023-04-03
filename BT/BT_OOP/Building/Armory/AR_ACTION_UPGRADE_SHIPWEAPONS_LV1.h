#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class AR_ACTION_UPGRADE_SHIPWEAPONS_LV1 : public BT_ACTION {
public:
    AR_ACTION_UPGRADE_SHIPWEAPONS_LV1(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchShipweaponslv1(void* data);
};
//----------