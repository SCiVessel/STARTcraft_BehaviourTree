#include "AC_DECO_CONDITION_RESEARCH_STIMPACKTECH.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

AC_DECO_CONDITION_RESEARCH_STIMPACKTECH::AC_DECO_CONDITION_RESEARCH_STIMPACKTECH(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchStimpacktech) {}


std::string AC_DECO_CONDITION_RESEARCH_STIMPACKTECH::GetDescription()
{
    return "DECO CONDITION RESEARCH STIMPACKTECH";
}

bool AC_DECO_CONDITION_RESEARCH_STIMPACKTECH::canResearchStimpacktech(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Stim_Packs))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 100 and gas < 100)
    {
        return false;
    }

    return true;
}
