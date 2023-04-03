#include "CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR::CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchMoebiusreactor) {}


std::string CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR::GetDescription()
{
    return "DECO CONDITION RESEARCH MOEBIUSREACTOR";
}

bool CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR::canResearchMoebiusreactor(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Moebius_Reactor) > 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 150 and gas < 150)
    {
        return false;
    }

    return true;
}
