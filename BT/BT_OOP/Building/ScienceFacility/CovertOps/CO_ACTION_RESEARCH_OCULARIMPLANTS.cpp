#include "CO_ACTION_RESEARCH_OCULARIMPLANTS.h"
#include "Tools.h"
#include "Data.h"

CO_ACTION_RESEARCH_OCULARIMPLANTS::CO_ACTION_RESEARCH_OCULARIMPLANTS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CO_ACTION_RESEARCH_OCULARIMPLANTS::Evaluate(void* data)
{
    return ReturnState(actionResearchOcularimplants(data));
}

std::string CO_ACTION_RESEARCH_OCULARIMPLANTS::GetDescription()
{
    return "ACTION RESEARCH OCULARIMPLANTS";
}

BT_NODE::State CO_ACTION_RESEARCH_OCULARIMPLANTS::actionResearchOcularimplants(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit covertops;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Covert_Ops && unit->isCompleted())
        {
            covertops = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (covertops->canUpgrade(BWAPI::UpgradeTypes::Ocular_Implants))
        {
            covertops->upgrade(BWAPI::UpgradeTypes::Ocular_Implants);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}