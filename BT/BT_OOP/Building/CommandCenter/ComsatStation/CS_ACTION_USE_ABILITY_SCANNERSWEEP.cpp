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

    auto& nukeDots = BWAPI::Broodwar->getNukeDots();

    if (pData->at_war || (!nukeDots.empty()))
    {
        for (auto& enemy : BWAPI::Broodwar->enemy()->getUnits())
        {
            if (enemy->exists())
            {
                if (enemy->isCloaked() || (enemy->isBurrowed()))
                {
                    if (enemy->getClosestUnit(BWAPI::Filter::IsOwned, 256))
                    {
                        unitToExecute->useTech(BWAPI::TechTypes::Scanner_Sweep, enemy);
                        return BT_NODE::SUCCESS;
                    }
                }
            }
        }
    }
    
    if (pData->enemyMainDestroyed)
    {
        for (size_t i = pData->sweepBaseLocation; i < pData->tilesOfExpansions.size(); i++)
        {
            if (BWAPI::Broodwar->isVisible(pData->tilesOfExpansions[pData->sweepBaseLocation]) == false)
            {
                unitToExecute->useTech(BWAPI::TechTypes::Scanner_Sweep, BWAPI::Position(pData->tilesOfExpansions[pData->sweepBaseLocation]));
                pData->sweepBaseLocation = i + 1;
                return BT_NODE::SUCCESS;
            }
        }
        pData->sweepBaseLocation = 0;
    }

    if (energyMax >= 200)
    {
        for (int m = 0; m < pData->tilesOfExpansions.size(); m++)
        {
            if (!BWAPI::Broodwar->isExplored(pData->tilesOfExpansions[pData->tilesOfExpansions.size() - 1 - m]))
            {
                unitToExecute->useTech(BWAPI::TechTypes::Scanner_Sweep, BWAPI::Position(pData->tilesOfExpansions[pData->tilesOfExpansions.size() - 1 - m]));
                return BT_NODE::SUCCESS;
            }
        }
    }

    return BT_NODE::FAILURE;
}
