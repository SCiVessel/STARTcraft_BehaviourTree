#include "SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX.h"
#include "Tools.h"
#include "Data.h"

SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX::SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX::Evaluate(void* data)
{
    return ReturnState(useAbilityDefensiveMatrix(data));
}

std::string SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX::GetDescription()
{
    return "ACTION USE ABILITY DEFENSIVEMATRIX";
}

BT_NODE::State SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX::useAbilityDefensiveMatrix(void* data)
{
    Data* pData = (Data*)data;

    int energy = 100;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Science_Vessel && unit->isCompleted())
        {
            auto allies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 320, BWAPI::Filter::IsAlly);
            if (unit->getEnergy() >= energy && allies.size())
            {
                BWAPI::Unitset alliesUnderAttack;
                for (auto a : allies)
                {
                    if (!a->getType().isBuilding() && a->isUnderAttack() && !a->getDefenseMatrixPoints())
                    {
                        alliesUnderAttack.insert(a);
                    }
                }

                if (!alliesUnderAttack.size())
                {
                    return BT_NODE::FAILURE;
                }

                BWAPI::Unit target;
                int supply = -1;
                for (auto a : alliesUnderAttack)
                {
                    int supplyA = a->getType().supplyRequired();
                    if (supplyA > supply)
                    {
                        supply = supplyA;
                    }
                }
                for (auto a : alliesUnderAttack)
                {
                    if (a->getType().supplyRequired() == supply)
                    {
                        target = a;
                        break;
                    }
                }

                if (unit->canUseTech(BWAPI::TechTypes::Defensive_Matrix, target))
                {
                    unit->useTech(BWAPI::TechTypes::Defensive_Matrix, target);
                    executed = true;
                }
            }
        }
    }

    if (executed)
    {
        return BT_NODE::SUCCESS;
    }
    else
    {
        return BT_NODE::FAILURE;
    }
}