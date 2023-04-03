#include "CO_ACTION_RESEARCH_MOEBIUSREACTOR.h"
#include "Tools.h"
#include "Data.h"

CO_ACTION_RESEARCH_MOEBIUSREACTOR::CO_ACTION_RESEARCH_MOEBIUSREACTOR(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CO_ACTION_RESEARCH_MOEBIUSREACTOR::Evaluate(void* data)
{
    return ReturnState(actionResearchMoebiusreactor(data));
}

std::string CO_ACTION_RESEARCH_MOEBIUSREACTOR::GetDescription()
{
    return "ACTION RESEARCH MOEBIUSREACTOR";
}

BT_NODE::State CO_ACTION_RESEARCH_MOEBIUSREACTOR::actionResearchMoebiusreactor(void* data)
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
        if (covertops->canUpgrade(BWAPI::UpgradeTypes::Moebius_Reactor))
        {
            covertops->upgrade(BWAPI::UpgradeTypes::Moebius_Reactor);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}