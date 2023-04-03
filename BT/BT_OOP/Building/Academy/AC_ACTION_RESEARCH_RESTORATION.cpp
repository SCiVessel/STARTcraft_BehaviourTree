#include "AC_ACTION_RESEARCH_RESTORATION.h"
#include "Tools.h"
#include "Data.h"

AC_ACTION_RESEARCH_RESTORATION::AC_ACTION_RESEARCH_RESTORATION(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AC_ACTION_RESEARCH_RESTORATION::Evaluate(void* data)
{
    return ReturnState(actionResearchRestoration(data));
}

std::string AC_ACTION_RESEARCH_RESTORATION::GetDescription()
{
    return "ACTION RESEARCH RESTORATION";
}

BT_NODE::State AC_ACTION_RESEARCH_RESTORATION::actionResearchRestoration(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Unit academy;
    bool found = false;

    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Academy && unit->isCompleted())
        {
            academy = unit;
            found = true;
            break;
        }
    }

    if (found)
    {
        if (academy->canResearch(BWAPI::TechTypes::Restoration))
        {
            academy->research(BWAPI::TechTypes::Restoration);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}