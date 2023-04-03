#include "ST_ACTION_USE_ABILITY_TANKMODE.h"
#include "Tools.h"
#include "Data.h"

ST_ACTION_USE_ABILITY_TANKMODE::ST_ACTION_USE_ABILITY_TANKMODE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State ST_ACTION_USE_ABILITY_TANKMODE::Evaluate(void* data)
{
    return ReturnState(useAbilityTankmode(data));
}

std::string ST_ACTION_USE_ABILITY_TANKMODE::GetDescription()
{
    return "ACTION USE ABILITY TANKMODE";
}

BT_NODE::State ST_ACTION_USE_ABILITY_TANKMODE::useAbilityTankmode(void* data)
{
    Data* pData = (Data*)data;
    bool executed;

    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        auto enemies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 288, BWAPI::Filter::IsEnemy);
        if (unit->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode && unit->isCompleted() && !enemies.size())
        {
            if (unit->canUnsiege())
            {
                unit->unsiege();
                executed = true;
            }
        }
    }

    if (!executed)
    {
        return BT_NODE::FAILURE;
    }
    else
    {
        return BT_NODE::SUCCESS;
    }
}