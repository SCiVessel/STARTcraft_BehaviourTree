#include "CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS::CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchOcularimplants) {}


std::string CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS::GetDescription()
{
    return "DECO CONDITION RESEARCH OCULARIMPLANTS";
}

bool CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS::canResearchOcularimplants(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
    {
        return false;
    }

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Ocular_Implants) > 0)
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
