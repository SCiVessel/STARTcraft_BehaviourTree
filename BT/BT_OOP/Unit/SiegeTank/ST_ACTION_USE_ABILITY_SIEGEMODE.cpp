#include "ST_ACTION_USE_ABILITY_SIEGEMODE.h"
#include "Tools.h"
#include "Data.h"

ST_ACTION_USE_ABILITY_SIEGEMODE::ST_ACTION_USE_ABILITY_SIEGEMODE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State ST_ACTION_USE_ABILITY_SIEGEMODE::Evaluate(void* data)
{
    return ReturnState(useAbilitySiegemode(data));
}

std::string ST_ACTION_USE_ABILITY_SIEGEMODE::GetDescription()
{
    return "ACTION USE ABILITY SIEGEMODE";
}

BT_NODE::State ST_ACTION_USE_ABILITY_SIEGEMODE::useAbilitySiegemode(void* data)
{
    Data* pData = (Data*)data;
    bool executed;

    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        auto enemies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 256, BWAPI::Filter::IsEnemy);
        if (unit->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode && unit->isCompleted() && enemies.size())
        {
            if (unit->canUseTech(BWAPI::TechTypes::Tank_Siege_Mode))
            {
                unit->useTech(BWAPI::TechTypes::Tank_Siege_Mode);
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