#include "UNIT_DECO_CONDITION_GO_COUNTER_ATTACK.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

UNIT_DECO_CONDITION_GO_COUNTER_ATTACK::UNIT_DECO_CONDITION_GO_COUNTER_ATTACK(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, goCounterAttack) {}


std::string UNIT_DECO_CONDITION_GO_COUNTER_ATTACK::GetDescription()
{
    return "UNIT_DECO_CONDITION_GO_COUNTER_ATTACK";
}

bool UNIT_DECO_CONDITION_GO_COUNTER_ATTACK::goCounterAttack(void *data)
{
    Data* pData = (Data*)data;
    
    // check if at war status cease
    if (pData->at_war && !pData->now_underattack && pData->not_underattack_counter >= COUNTER_ATTACK_THRESHOLD)
    {
        // reset recorder
        pData->at_war = false;
        pData->not_underattack_counter = 0;
        
        return true;
    }

    return false;
}
