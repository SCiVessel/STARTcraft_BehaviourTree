#include "AC_ACTION_RESEARCH_STIMPACKTECH.h"
#include "Tools.h"
#include "Data.h"

AC_ACTION_RESEARCH_STIMPACKTECH::AC_ACTION_RESEARCH_STIMPACKTECH(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AC_ACTION_RESEARCH_STIMPACKTECH::Evaluate(void* data)
{
    return ReturnState(actionResearchStimpacktech(data));
}

std::string AC_ACTION_RESEARCH_STIMPACKTECH::GetDescription()
{
    return "ACTION RESEARCH STIMPACKTECH";
}

BT_NODE::State AC_ACTION_RESEARCH_STIMPACKTECH::actionResearchStimpacktech(void* data)
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
        if (academy->canResearch(BWAPI::TechTypes::Stim_Packs))
        {
            academy->research(BWAPI::TechTypes::Stim_Packs);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}