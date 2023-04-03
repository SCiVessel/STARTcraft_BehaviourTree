#include "CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR::CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchApolloreactor) {}


std::string CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR::GetDescription()
{
    return "DECO CONDITION RESEARCH APOLLOREACTOR";
}

bool CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR::canResearchApolloreactor(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->getUpgradeLevel(BWAPI::UpgradeTypes::Apollo_Reactor) > 0)
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 200 and gas < 200)
    {
        return false;
    }

    int wraiths = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Wraith, BWAPI::Broodwar->self()->getUnits());
    if (wraiths >= 10)
    {
        return true;
    }

    return false;
}
