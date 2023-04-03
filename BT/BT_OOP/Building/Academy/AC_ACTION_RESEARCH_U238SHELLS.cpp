#include "AC_ACTION_RESEARCH_U238SHELLS.h"
#include "Tools.h"
#include "Data.h"

AC_ACTION_RESEARCH_U238SHELLS::AC_ACTION_RESEARCH_U238SHELLS(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AC_ACTION_RESEARCH_U238SHELLS::Evaluate(void* data)
{
    return ReturnState(actionResearchU238shells(data));
}

std::string AC_ACTION_RESEARCH_U238SHELLS::GetDescription()
{
    return "ACTION RESEARCH U238SHELLS";
}

BT_NODE::State AC_ACTION_RESEARCH_U238SHELLS::actionResearchU238shells(void* data)
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
        if (academy->canUpgrade(BWAPI::UpgradeTypes::U_238_Shells))
        {
            academy->upgrade(BWAPI::UpgradeTypes::U_238_Shells);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}