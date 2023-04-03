#include "CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD::CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name, parent, canResearchCloakingfield) {}


std::string CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD::GetDescription()
{
    return "DECO CONDITION RESEARCH CLOAKINGFIELD";
}

bool CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD::canResearchCloakingfield(void* data)
{
    Data* pData = (Data*)data;

    if (BWAPI::Broodwar->self()->hasResearched(BWAPI::TechTypes::Cloaking_Field))
    {
        return false;
    }

    int minerals = BWAPI::Broodwar->self()->minerals();
    int gas = BWAPI::Broodwar->self()->gas();

    if (minerals < 150 and gas < 150)
    {
        return false;
    }

    int wraiths = Tools::CountUnitsOfType(BWAPI::UnitTypes::Terran_Wraith, BWAPI::Broodwar->self()->getUnits());
    if (wraiths >= 4)
    {
        return true;
    }

    return false;
}
