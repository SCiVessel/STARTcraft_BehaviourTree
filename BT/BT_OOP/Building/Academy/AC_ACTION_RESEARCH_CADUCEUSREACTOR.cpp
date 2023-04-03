#include "AC_ACTION_RESEARCH_CADUCEUSREACTOR.h"
#include "Tools.h"
#include "Data.h"

AC_ACTION_RESEARCH_CADUCEUSREACTOR::AC_ACTION_RESEARCH_CADUCEUSREACTOR(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State AC_ACTION_RESEARCH_CADUCEUSREACTOR::Evaluate(void* data)
{
    return ReturnState(actionResearchCaduceusreactor(data));
}

std::string AC_ACTION_RESEARCH_CADUCEUSREACTOR::GetDescription()
{
    return "ACTION RESEARCH CADUCEUSREACTOR";
}

BT_NODE::State AC_ACTION_RESEARCH_CADUCEUSREACTOR::actionResearchCaduceusreactor(void* data)
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
        if (academy->canUpgrade(BWAPI::UpgradeTypes::Caduceus_Reactor))
        {
            academy->upgrade(BWAPI::UpgradeTypes::Caduceus_Reactor);
            return BT_NODE::SUCCESS;
        }
    }

    return BT_NODE::FAILURE;
}