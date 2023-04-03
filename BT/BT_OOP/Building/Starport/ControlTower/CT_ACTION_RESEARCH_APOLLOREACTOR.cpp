#include "CT_ACTION_RESEARCH_APOLLOREACTOR.h"
#include "Tools.h"
#include "Data.h"

CT_ACTION_RESEARCH_APOLLOREACTOR::CT_ACTION_RESEARCH_APOLLOREACTOR(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CT_ACTION_RESEARCH_APOLLOREACTOR::Evaluate(void* data)
{
    return ReturnState(actionResearchApolloreactor(data));
}

std::string CT_ACTION_RESEARCH_APOLLOREACTOR::GetDescription()
{
    return "ACTION RESEARCH APOLLOREACTOR";
}

BT_NODE::State CT_ACTION_RESEARCH_APOLLOREACTOR::actionResearchApolloreactor(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit controltower;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Control_Tower && unit->isCompleted())
        {
            controltower = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (controltower->canUpgrade(BWAPI::UpgradeTypes::Apollo_Reactor))
        {
            controltower->upgrade(BWAPI::UpgradeTypes::Apollo_Reactor);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}