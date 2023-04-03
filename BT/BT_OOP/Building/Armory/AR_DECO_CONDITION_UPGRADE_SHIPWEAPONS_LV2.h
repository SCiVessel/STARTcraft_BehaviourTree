#pragma once
#include <cassert>
#include "BT_DECO_CONDITION.h"

//Evaluates the specified conditional task. If the conditional task returns success then the child task is run and the child status is returned. If the conditional task does not
// return success then the child task is not run and a failure status is immediately returned.
// 
//--------------------
class AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV2 : public BT_DECO_CONDITION {
public:
    AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV2(std::string name, BT_NODE* parent);
    std::string GetDescription() override;

    static bool canUpgradeShipweaponslv2(void* data);
};
//----------