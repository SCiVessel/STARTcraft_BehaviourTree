#include "SF_DECO_CONDITION_RESEARCH_IRRADIATE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

SF_DECO_CONDITION_RESEARCH_IRRADIATE::SF_DECO_CONDITION_RESEARCH_IRRADIATE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchIrradiate) {}


std::string SF_DECO_CONDITION_RESEARCH_IRRADIATE::GetDescription()
{
    return "DECO CONDITION RESEARCH IRRADIATE";
}

bool SF_DECO_CONDITION_RESEARCH_IRRADIATE::canResearchIrradiate(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Irradiate))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 200 and gas < 200)
    {
        return false;
    }

    return true;
}
