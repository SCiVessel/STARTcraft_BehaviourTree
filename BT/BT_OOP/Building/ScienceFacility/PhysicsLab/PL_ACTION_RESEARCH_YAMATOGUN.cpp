#include "PL_ACTION_RESEARCH_YAMATOGUN.h"
#include "Tools.h"
#include "Data.h"

PL_ACTION_RESEARCH_YAMATOGUN::PL_ACTION_RESEARCH_YAMATOGUN(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State PL_ACTION_RESEARCH_YAMATOGUN::Evaluate(void* data)
{
    return ReturnState(actionResearchYamatogun(data));
}

std::string PL_ACTION_RESEARCH_YAMATOGUN::GetDescription()
{
    return "ACTION RESEARCH YAMATOGUN";
}

BT_NODE::State PL_ACTION_RESEARCH_YAMATOGUN::actionResearchYamatogun(void* data)
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
        if (physicslab->canResearch(BWAPI::TechTypes::Yamato_Gun))
        {
            physicslab->research(BWAPI::TechTypes::Yamato_Gun);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}