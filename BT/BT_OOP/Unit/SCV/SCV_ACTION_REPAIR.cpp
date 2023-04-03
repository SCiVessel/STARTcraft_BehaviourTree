#include "SCV_ACTION_REPAIR.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_REPAIR::SCV_ACTION_REPAIR(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State SCV_ACTION_REPAIR::Evaluate(void* data)
{
    return ReturnState(actionRepair(data));
}

std::string SCV_ACTION_REPAIR::GetDescription()
{
    return "ACTION REPAIR";
}

BT_NODE::State SCV_ACTION_REPAIR::actionRepair(void* data)
{
    Data* pData = (Data*)data;

    int mineral = 50;
    int gas = 20;
    for (auto unit : BWAPI::Broodwar->self()->getUnits())
    {
        auto alliesRepairable = BWAPI::Broodwar->getUnitsInRadius(unit->getPosition(), 256, BWAPI::Filter::IsAlly && (BWAPI::Filter::IsBuilding || BWAPI::Filter::IsMechanical));
        if (unit->getType() == BWAPI::UnitTypes::Terran_SCV && unit->isCompleted())
        {
            if (BWAPI::Broodwar->self()->minerals() >= mineral and BWAPI::Broodwar->self()->gas() >= gas)
            {
                BWAPI::Unitset targetsRepair;
                for (auto ar : alliesRepairable)
                {
                    if ((float)ar->getHitPoints() / (float)ar->getInitialHitPoints() < 0.4)
                    {
                        targetsRepair.insert(ar);
                    }
                }
                if (!targetsRepair.size())
                {
                    return BT_NODE::FAILURE;
                }

                float hpPercent = 1.0f;
                BWAPI::Unit target;
                for (auto tr : targetsRepair)
                {
                    float hpP = (float)tr->getHitPoints() / (float)tr->getInitialHitPoints();
                    if (hpP < hpPercent)
                    {
                        hpPercent = hpP;
                        target = tr;
                    }
                }

                if (unit->canRepair(target))
                {
                    unit->repair(target);
                    for (auto& check : pData->unitsFarmingMinerals)
                    {
                        if (check.contains(unit))
                        {
                            check.erase(unit);
                            break;
                        }
                    }
                    for (auto& check : pData->unitsFarmingGeysers)
                    {
                        if (check.contains(unit))
                        {
                            check.erase(unit);
                            break;
                        }
                    }
                    return BT_NODE::SUCCESS;
                }
            }
        }
    }

    return BT_NODE::FAILURE;
}