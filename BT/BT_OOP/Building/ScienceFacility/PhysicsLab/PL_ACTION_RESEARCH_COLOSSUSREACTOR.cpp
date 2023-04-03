#include "PL_ACTION_RESEARCH_COLOSSUSREACTOR.h"
#include "Tools.h"
#include "Data.h"

PL_ACTION_RESEARCH_COLOSSUSREACTOR::PL_ACTION_RESEARCH_COLOSSUSREACTOR(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State PL_ACTION_RESEARCH_COLOSSUSREACTOR::Evaluate(void* data)
{
    return ReturnState(actionResearchColossusreactor(data));
}

std::string PL_ACTION_RESEARCH_COLOSSUSREACTOR::GetDescription()
{
    return "ACTION RESEARCH COLOSSUSREACTOR";
}

BT_NODE::State PL_ACTION_RESEARCH_COLOSSUSREACTOR::actionResearchColossusreactor(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit physicslab;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Physics_Lab && unit->isCompleted())
        {
            physicslab = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (physicslab->canUpgrade(BWAPI::UpgradeTypes::Colossus_Reactor))
        {
            physicslab->upgrade(BWAPI::UpgradeTypes::Colossus_Reactor);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}