#include "SCV_DECO_CONDITION_EARLY_GAME_SCOUTING.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SCV_DECO_CONDITION_EARLY_GAME_SCOUTING::SCV_DECO_CONDITION_EARLY_GAME_SCOUTING(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, EarlyGameScouting) {}


std::string SCV_DECO_CONDITION_EARLY_GAME_SCOUTING::GetDescription()
{
    return "SCV_DECO_CONDITION_EARLY_GAME_SCOUTING";
}

bool SCV_DECO_CONDITION_EARLY_GAME_SCOUTING::EarlyGameScouting(void *data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() >= EARLY_GAME_SCOUT_TIMING)
    {
        return true;
    }

    return false;
}
