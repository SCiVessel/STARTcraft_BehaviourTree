#include "SF_DECO_CONDITION_RESEARCH_TITANREACTOR.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SF_DECO_CONDITION_RESEARCH_TITANREACTOR::SF_DECO_CONDITION_RESEARCH_TITANREACTOR(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchTitanreactor) {}


std::string SF_DECO_CONDITION_RESEARCH_TITANREACTOR::GetDescription()
{
    return "DECO CONDITION RESEARCH TITANREACTOR";
}

bool SF_DECO_CONDITION_RESEARCH_TITANREACTOR::canResearchTitanreactor(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Titan_Reactor) > 0)
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
