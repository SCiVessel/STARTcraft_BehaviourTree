#include "VT_ACTION_USE_ABILITY_SPIDERMINE.h"
#include "Tools.h"
#include "Data.h"

inline float frand() { return (float)rand() / (float)RAND_MAX; }
inline float urand(float a, float b) { return a + (b - a) * frand(); }

VT_ACTION_USE_ABILITY_SPIDERMINE::VT_ACTION_USE_ABILITY_SPIDERMINE(std::string name,BT_NODE* parent)
    :  BT_ACTION(name,parent) {}

BT_NODE::State VT_ACTION_USE_ABILITY_SPIDERMINE::Evaluate(void* data)
{
    return ReturnState(useAbilitySpidermine(data));
}

std::string VT_ACTION_USE_ABILITY_SPIDERMINE::GetDescription()
{
    return "ACTION USE ABILITY SPIDERMINE";
}

BT_NODE::State VT_ACTION_USE_ABILITY_SPIDERMINE::useAbilitySpidermine(void* data)
{
    Data* pData = (Data*)data;

    bool executed = false;
    auto units = BWAPI::Broodwar->self()->getUnits();
    for (auto unit : units)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Vulture && unit->isCompleted())
        {
            BWAPI::Unit siegeTank;
            float minDist = -1.0f;
            for (auto tank : units)
            {
                if (unit->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode)
                {
                    float dist = unit->getDistance(tank);
                    if (minDist < 0 || minDist > dist)
                    {
                        minDist = dist;
                        siegeTank = tank;
                    }
                }
            }

            if (minDist > 0)
            {
                auto position = siegeTank->getPosition();
                int randomPositionX = int(urand(-2, 2));
                int randomPositionY = int(urand(-2, 2));
                if (!randomPositionX && !randomPositionY)
                {
                    randomPositionX += 1;
                }
                BWAPI::Position p(position.x + randomPositionX, position.y + randomPositionY);

                if (unit->canUseTech(BWAPI::TechTypes::Spider_Mines, p))
                {
                    unit->useTech(BWAPI::TechTypes::Spider_Mines, p);
                    return BT_NODE::SUCCESS;
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