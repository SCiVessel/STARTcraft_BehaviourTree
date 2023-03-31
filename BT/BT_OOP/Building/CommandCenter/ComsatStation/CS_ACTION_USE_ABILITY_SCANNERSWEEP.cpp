#include "CS_ACTION_USE_ABILITY_SCANNERSWEEP.h"
#include "Tools.h"
#include "Data.h"

CS_ACTION_USE_ABILITY_SCANNERSWEEP::CS_ACTION_USE_ABILITY_SCANNERSWEEP(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State CS_ACTION_USE_ABILITY_SCANNERSWEEP::Evaluate(void* data)
{
    return ReturnState(useAbilityScannerSweep(data));
}

std::string CS_ACTION_USE_ABILITY_SCANNERSWEEP::GetDescription()
{
    return "SCANNING AREA";
}


BT_NODE::State CS_ACTION_USE_ABILITY_SCANNERSWEEP::useAbilityScannerSweep(void* data)
{
    Data* pData = (Data*)data;

    BWAPI::Position beacon;

    // For each unit that we own
    int energyMax = 0;
    BWAPI::Unit unitToExecute;
    for (auto& unit : BWAPI::Broodwar->self()->getUnits())
    {
        // if the unit is of the correct type, and it actually has been constructed, return it
        if (unit->getType() == BWAPI::UnitTypes::Terran_Comsat_Station && unit->isCompleted())
        {
            if (unit->getEnergy() > energyMax)
            {
                energyMax = unit->getEnergy();
                unitToExecute = unit;
            }
        }
    }

    if (energyMax < 50)
    {
        return BT_NODE::FAILURE;
    }

    if (pData->at_war)
    {
        for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits())
        {
            if (enemy->exists())
            {
                if (enemy->isCloaked() || enemy->isBurrowed())
                {
                    unitToExecute->useTech(BWAPI::TechTypes::Scanner_Sweep, enemy);
                    return BT_NODE::SUCCESS;
                }
            }
        }
    }
    else if (energyMax >= 200)
    {
        for (int m = 0; m < pData->tilesOfExpansions.size(); m++)
        {
            for (int n = 0; n < pData->tilesOfExpansions[m].size(); n++)
            {
                if (!BWAPI::Broodwar->isExplored(pData->tilesOfExpansions[m][n]))
                {
                    unitToExecute->useTech(BWAPI::TechTypes::Scanner_Sweep, BWAPI::Position(pData->tilesOfExpansions[m][n]));
                    return BT_NODE::SUCCESS;
                }
            }
        }
    }

    return BT_NODE::FAILURE;
}
