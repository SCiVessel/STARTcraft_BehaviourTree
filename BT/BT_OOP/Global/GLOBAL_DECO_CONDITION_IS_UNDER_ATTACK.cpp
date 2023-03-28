#include "GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK::GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsUnderAttack) {}


std::string GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK::GetDescription()
{
    return "GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK";
}

bool GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK::IsUnderAttack(void *data)
{
    Data* pData = (Data*)data;
    
    // Check if we are being attacked
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // WE ARE UNDER ATTACK
        if (unit->isUnderAttack())
        {
            return true;
        }
    }

    return false;
}
