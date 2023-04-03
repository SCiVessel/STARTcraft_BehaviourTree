#include "MD_ACTION_USE_ABILITY_RESTORATION.h"
#include "Tools.h"
#include "Data.h"

MD_ACTION_USE_ABILITY_RESTORATION::MD_ACTION_USE_ABILITY_RESTORATION(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State MD_ACTION_USE_ABILITY_RESTORATION::Evaluate(void* data)
{
    return ReturnState(useAbilityRestoration(data));
}

std::string MD_ACTION_USE_ABILITY_RESTORATION::GetDescription()
{
    return "ACTION USE ABILITY RESTORATION";
}

BT_NODE::State MD_ACTION_USE_ABILITY_RESTORATION::useAbilityRestoration(void* data)
{
    Data* pData = (Data*)data;

    int energy = 50;
    bool executed = false;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Medic && unit->isCompleted())
        {
            auto allies = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 192, BWAPI::Filter::IsAlly);
            if (unit->getEnergy() >= energy && allies.size())
            {
                BWAPI::Unitset controlledAllies;
                for (auto a : allies)
                {
                    if (!a->getType().isBuilding())
                    {
                        if (a->isLockedDown() || a->isBlind() || a->isIrradiated() || a->isPlagued() || a->isEnsnared() || a->isParasited() || a->isMaelstrommed())
                        {
                            controlledAllies.insert(a);
                        }
                    }
                }

                if (!controlledAllies.size())
                {
                    return BT_NODE::FAILURE;
                }

                BWAPI::Unit target;
                int supply = -1;
                for (auto a : controlledAllies)
                {
                    int supplyA = a->getType().supplyRequired();
                    if (supplyA > supply)
                    {
                        supply = supplyA;
                    }
                }
                for (auto a : controlledAllies)
                {
                    if (a->getType().supplyRequired() == supply)
                    {
                        target = a;
                        break;
                    }
                }

                if (unit->canUseTech(BWAPI::TechTypes::Restoration, target))
                {
                    unit->useTech(BWAPI::TechTypes::Restoration, target);
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