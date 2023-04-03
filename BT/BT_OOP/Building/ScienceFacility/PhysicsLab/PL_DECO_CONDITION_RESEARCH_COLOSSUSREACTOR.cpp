#include "PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR::PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchColossusreactor) {}


std::string PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR::GetDescription()
{
    return "DECO CONDITION RESEARCH COLOSSUSREACTOR";
}

bool PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR::canResearchColossusreactor(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Colossus_Reactor) > 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 150 and gas < 150)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Yamato_Gun))
    {
        return true;
    }

    return false;
}
