#include "AC_ACTION_RESEARCH_OPTICFLARE.h"
#include "Tools.h"
#include "Data.h"

AC_ACTION_RESEARCH_OPTICFLARE::AC_ACTION_RESEARCH_OPTICFLARE(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AC_ACTION_RESEARCH_OPTICFLARE::Evaluate(void* data)
{
    return ReturnState(actionResearchOpticflare(data));
}

std::string AC_ACTION_RESEARCH_OPTICFLARE::GetDescription()
{
    return "ACTION RESEARCH OPTICFLARE";
}

BT_NODE::State AC_ACTION_RESEARCH_OPTICFLARE::actionResearchOpticflare(void* data)
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
        if (academy->canResearch(BWAPI::TechTypes::Optical_Flare))
        {
            academy->research(BWAPI::TechTypes::Optical_Flare);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}