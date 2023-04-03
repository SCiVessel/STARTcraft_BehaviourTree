#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

//--------------------
class EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV1 : public BT_ACTION {
public:
    EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV1(std::string name, BT_NODE* parent);

private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;
    static BT_NODE::State actionResearchInfantryweaponslv1(void* data);
};
//----------