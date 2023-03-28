#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Data.h>
#include <format>

#include "BT.h"

#include "DataController.h"

StarterBot::StarterBot()
{
    pData = new Data();
    pData->currMinerals = 0;
    // pData->thresholdMinerals = THRESHOLD1_MINERALS;
    pData->currSupply = 0;
    pData->thresholdSupply = EARLY_GAME_SUPPLY_THRESHOLD;

    pData->nWantedBarracksTotal = 1;

    // pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;
    // pData->nWantedWorkersFarmingMinerals = NWANTED_WORKERS_FARMING_MINERALS;

    // initalize the list to keep the workers to each command center
    std::unordered_set<BWAPI::Unit> command_center_mineralsFarmer_list;
    pData->unitsFarmingMinerals.push_back(command_center_mineralsFarmer_list);
    std::unordered_set<BWAPI::Unit> command_center_geysersFarmer_list;
    pData->unitsFarmingGeysers.push_back(command_center_geysersFarmer_list);
    int nWWFM = 18;
    pData->nWantedWorkersFarmingMinerals.push_back(nWWFM);
    int nWWFG = 3;
    pData->nWantedWorkersFarmingGeysers.push_back(nWWFG);
    int nWWT = nWWFM + nWWFG;
    pData->nWantedWorkersTotal.push_back(nWWT);

    // find initial command center position
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : unitSet)
    {
        if (unit->getType() == BWAPI::UnitTypes::Terran_Command_Center)
        {
            pData->CommandCenters.push_back(unit);
            pData->tilePositionCommandCenters.push_back(unit->getTilePosition());
            pData->positionCommandCenters.push_back(unit->getPosition());

        /*    BWAPI::Unitset temp = unit->getUnitsInRadius(128, BWAPI::Filter::IsResourceContainer);
            if (!temp.empty())
            {
                for (auto& resource : temp) {
                    if (resource->getType() == BWAPI::UnitTypes::Resource_Vespene_Geyser)
                    {
                        pData->availableGeysers.insert(resource);
                    }
                }
            }
        */
            break;
        }
    }

    pBtTest = nullptr;
    /*
    //Test BT nodes: BT_DECO_COND_GREATER_THAN, BT_DECO_COND_LESSER_THAN, BT_ACTION_LOG
    pBtTest = new BT_DECORATOR("EntryPoint", nullptr);
    BT_DECO_REPEATER* pForeverRepeater = new BT_DECO_REPEATER("RepeatForever", pBtTest, 0, true, false, false);
    //BT_DECO_COND_GREATER_THAN<int>* pGreaterThan = new BT_DECO_COND_GREATER_THAN<int>("MineralsGreaterThanThreshold1", pForeverRepeater, THRESHOLD1_MINERALS, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pGreaterThan, std::format("current minerals greater than {}", THRESHOLD1_MINERALS));
    BT_DECO_COND_LESSER_THAN<int>* pLesserThan = new BT_DECO_COND_LESSER_THAN<int>("MineralsLesserThanThreshold1", pForeverRepeater, THRESHOLD1_MINERALS, pData->currMinerals, false);
    BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pLesserThan, std::format("current minerals lesser than {}", THRESHOLD1_MINERALS));
    */

    //Test BT nodes: BT_DECO_REPEATER (resetOnRepeat = true), BT_COND_GREATER_THAN, BT_COND_LESSER_THAN, BT_ACTION_LOG
    pBtTest = new BT_DECORATOR("EntryPoint", nullptr);
    BT_DECO_REPEATER* pForeverRepeater = new BT_DECO_REPEATER("RepeatForever", pBtTest, 0, true, false, true);
    BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer", pForeverRepeater, 2);
    //BT_COND_GREATER_THAN<int> *pGreaterThan = new BT_COND_GREATER_THAN<int>("MineralsGreaterThanThreshold1",pSequencer,100, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pSequencer, std::format("current minerals greater than {}", 100));
    BT_COND_LESSER_THAN<int>* pLesserThan = new BT_COND_LESSER_THAN<int>("MineralsLesserThanThreshold1", pSequencer, 100, pData->currMinerals, false);
    BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pSequencer, std::format("current minerals lesser than {}", 100));



    // Starcraft AI BT
    pBT = new BT_DECORATOR("EntryPoint", nullptr);

    //Main Parrallel Sequence
    BT_PARALLEL_SEQUENCER* pParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBT, 20);

        //--------------------------------------------------------------Global--------------------------------------------------------------//
        
        //-------------------------------------------------------------Building-------------------------------------------------------------//
        
        //Command Center
        //Train Worker
        BT_DECO_REPEATER* pTrainingWorkersForeverRepeater = new BT_DECO_REPEATER("RepeatForeverTrainingWorkers", pParallelSeq, 0, true, false, false);
        BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", pTrainingWorkersForeverRepeater);
        CC_ACTION_TRAIN_WORKER* pTrainWorker = new CC_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkers);

        //Add-ons


        //Barracks
        BT_DECO_REPEATER* pBarracksTrainingForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBarracksTraining", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectBarracksUnit = new BT_SELECTOR("SelectBarracksUnit", pBarracksTrainingForeverRepeater, 4);
        
            //Train Ghost
            

            //Train Medic
            BA_DECO_CONDITION_NOT_ENOUGH_MEDIC* pNotEnoughMedic = new BA_DECO_CONDITION_NOT_ENOUGH_MEDIC("NotEnoughMedic", pSelectBarracksUnit);
            BA_ACTION_TRAIN_MEDIC* pTrainMedic = new BA_ACTION_TRAIN_MEDIC("TrainMedic", pNotEnoughMedic);

            //Train Firebat
            BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT* pNotEnoughFirebat = new BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT("NotEnoughFirebat", pSelectBarracksUnit);
            BA_ACTION_TRAIN_FIREBAT* pTrainFirebat = new BA_ACTION_TRAIN_FIREBAT("TrainFirebat", pNotEnoughFirebat);

            //Train Marine
            BA_DECO_CONDITION_NOT_ENOUGH_MARINE* pNotEnoughMarine = new BA_DECO_CONDITION_NOT_ENOUGH_MARINE("NotEnoughMarine", pSelectBarracksUnit);
            BA_ACTION_TRAIN_MARINE* pTrainMarine = new BA_ACTION_TRAIN_MARINE("TrainMarine", pNotEnoughMarine);   


        //Factory
        BT_DECO_REPEATER* pFactoryTrainingForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFactoryTraining", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectFactoryUnit = new BT_SELECTOR("SelectFactoryUnit", pFactoryTrainingForeverRepeater, 3);

            //Train Goliath
            //BA_DECO_CONDITION_NOT_ENOUGH_MEDIC* pNotEnoughMedic = new BA_DECO_CONDITION_NOT_ENOUGH_MEDIC("NotEnoughMedic", pSelectFactoryUnit);
            //BA_ACTION_TRAIN_MEDIC* pTrainMedic = new BA_ACTION_TRAIN_MEDIC("TrainMedic", pNotEnoughMedic);

            //Train Vulture
            FA_DECO_CONDITION_NOT_ENOUGH_VULTURE* pNotEnoughVulture = new FA_DECO_CONDITION_NOT_ENOUGH_VULTURE("NotEnoughVulture", pSelectFactoryUnit);
            FA_ACTION_TRAIN_VULTURE* pTrainVulture = new FA_ACTION_TRAIN_VULTURE("TrainVulture", pNotEnoughVulture);

            //Train Siege Tank
            //BA_DECO_CONDITION_NOT_ENOUGH_MARINE* pNotEnoughMarine = new BA_DECO_CONDITION_NOT_ENOUGH_MARINE("NotEnoughMarine", pSelectFactoryUnit);
            //BA_ACTION_TRAIN_MARINE* pTrainMarine = new BA_ACTION_TRAIN_MARINE("TrainMarine", pNotEnoughMarine);

        //Starport
        BT_DECO_REPEATER* pStarportTrainingForeverRepeater = new BT_DECO_REPEATER("RepeatForeverStarportTraining", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectStarportUnit = new BT_SELECTOR("SelectStarportUnit", pStarportTrainingForeverRepeater, 5);

            //Train Battlecruiser
            //BA_DECO_CONDITION_NOT_ENOUGH_MEDIC* pNotEnoughMedic = new BA_DECO_CONDITION_NOT_ENOUGH_MEDIC("NotEnoughMedic", pSelectFactoryUnit);
            //BA_ACTION_TRAIN_MEDIC* pTrainMedic = new BA_ACTION_TRAIN_MEDIC("TrainMedic", pNotEnoughMedic);

            //Train Science Vessel
            //BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT* pNotEnoughFirebat = new BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT("NotEnoughFirebat", pSelectFactoryUnit);
            //BA_ACTION_TRAIN_FIREBAT* pTrainFirebat = new BA_ACTION_TRAIN_FIREBAT("TrainFirebat", pNotEnoughFirebat);

            //Train Valkyrie
            //BA_DECO_CONDITION_NOT_ENOUGH_MARINE* pNotEnoughMarine = new BA_DECO_CONDITION_NOT_ENOUGH_MARINE("NotEnoughMarine", pSelectFactoryUnit);
            //BA_ACTION_TRAIN_MARINE* pTrainMarine = new BA_ACTION_TRAIN_MARINE("TrainMarine", pNotEnoughMarine);

            //Train Dropship

            //Train Wraith
            SP_DECO_CONDITION_NOT_ENOUGH_WRAITH* pNotEnoughWraith = new SP_DECO_CONDITION_NOT_ENOUGH_WRAITH("NotEnoughWraith", pSelectStarportUnit);
            SP_ACTION_TRAIN_WRAITH* pTrainWraith = new SP_ACTION_TRAIN_WRAITH("TrainWraith", pNotEnoughWraith);

        //---------------------------------------------------------------Unit---------------------------------------------------------------//
        
        //SCV
        // Farming Sequence
        BT_DECO_REPEATER* pFarmingForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFarming", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pCheckGeyserAndMineral = new BT_SELECTOR("CheckGeyserAndMineral", pFarmingForeverRepeater, 2);
            //Farming Vespene Gas forever
            SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER* pNotEnoughWorkersFarmingGeyser = new SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER("NotEnoughWorkersFarmingGeyser", pCheckGeyserAndMineral);
            SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY* pSendWorkerToGeyser = new SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY("SendWorkerToRefinery", pNotEnoughWorkersFarmingGeyser);
            //Farming Minerals forever
            BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS* pNotEnoughWorkersFarmingMinerals = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS("NotEnoughWorkersFarmingMinerals", pCheckGeyserAndMineral);
            SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS* pSendWorkerToMinerals = new SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS("SendWorkerToMinerals", pNotEnoughWorkersFarmingMinerals);
        
        // Constructing Sequence
            //Build Supply Provider
            BT_DECO_REPEATER* pBuildSupplyProviderForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildSupplyProvider", pParallelSeq, 0, true, false, false);
            BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pBuildSupplyProviderForeverRepeater);
            SCV_ACTION_BUILD_SUPPLY_PROVIDER* pBuildSupplyProvider = new SCV_ACTION_BUILD_SUPPLY_PROVIDER("BuildSupplyProvider", pNotEnoughSupply);
    
            //Build Barracks
            BT_DECO_REPEATER* pBuildBarracksForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildBarracks", pParallelSeq, 0, true, false, true);
            BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS* pNotEnoughBarracks = new BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS("NotEnoughBarracks", pBuildBarracksForeverRepeater);

                BT_SEQUENCER* pBuildBarracksAndWait = new BT_SEQUENCER("BuildBarracksAndWait", pNotEnoughBarracks, 2);
                
                BT_ACTION_WAIT* pBarrackWait = new BT_ACTION_WAIT("WaitForResponse", pBuildBarracksAndWait, 3);
                SCV_ACTION_BUILD_BARRACKS* pBuildBarracks = new SCV_ACTION_BUILD_BARRACKS("BuildBarracks", pBuildBarracksAndWait);
            
            //Build Vespene Geyser
            BT_DECO_REPEATER* pBuildVespeneGeyserForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildVespeneGeyser", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY* pNotEnoughVespeneGeyser = new SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY("NotEnoughVespeneGeyser", pBuildVespeneGeyserForeverRepeater);

                BT_SEQUENCER* pBuildVespeneGeyserAndWait = new BT_SEQUENCER("BuildGeyserAndWait", pNotEnoughVespeneGeyser, 2);

                BT_ACTION_WAIT* pVespeneGeyserWait = new BT_ACTION_WAIT("WaitForResponse", pBuildVespeneGeyserAndWait, 3);
                SCV_ACTION_BUILD_REFINERY* pBuildVespeneGeyser = new SCV_ACTION_BUILD_REFINERY("BuildVespeneGeyser", pBuildVespeneGeyserAndWait);

            //Build Academy
            BT_DECO_REPEATER* pBuildAcademyForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildAcademy", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY* pNotEnoughAcademy = new SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY("NotEnoughAcademy", pBuildAcademyForeverRepeater);

                BT_SEQUENCER* pBuildAcademyAndWait = new BT_SEQUENCER("BuildAcademyAndWait", pNotEnoughAcademy, 2);

                BT_ACTION_WAIT* pAcademyWait = new BT_ACTION_WAIT("WaitForResponse", pBuildAcademyAndWait, 3);
                SCV_ACTION_BUILD_ACADEMY* pBuildAcademy = new SCV_ACTION_BUILD_ACADEMY("BuildVespeneGeyser", pBuildAcademyAndWait);

            //Build Factory
            BT_DECO_REPEATER* pBuildFactoryForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildFactory", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY* pNotEnoughFactory = new SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY("NotEnoughFactory", pBuildFactoryForeverRepeater);

                BT_SEQUENCER* pBuildFactoryAndWait = new BT_SEQUENCER("BuildFactoryAndWait", pNotEnoughFactory, 2);

                BT_ACTION_WAIT* pFactoryWait = new BT_ACTION_WAIT("WaitForResponse", pBuildFactoryAndWait, 3);
                SCV_ACTION_BUILD_FACTORY* pBuildFactory = new SCV_ACTION_BUILD_FACTORY("BuildFactory", pBuildFactoryAndWait);

            //Build Starport
            BT_DECO_REPEATER* pBuildStarportForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildStarport", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT* pNotEnoughStarport = new SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT("NotEnoughStarport", pBuildStarportForeverRepeater);

                BT_SEQUENCER* pBuildStarportAndWait = new BT_SEQUENCER("BuildStarportAndWait", pNotEnoughStarport, 2);

                BT_ACTION_WAIT* pStarportWait = new BT_ACTION_WAIT("WaitForResponse", pBuildStarportAndWait, 3);
                SCV_ACTION_BUILD_STARPORT* pBuildStarport = new SCV_ACTION_BUILD_STARPORT("BuildStarport", pBuildStarportAndWait);

            

        //For all Units:
        //Retributive Attack
        BT_DECO_REPEATER* pRetributionForeverRepeater = new BT_DECO_REPEATER("RepeatForeverRetribute", pParallelSeq, 0, true, false, true);
        GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK* pIsUnderAttack = new GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK("WeAreUnderAttack", pRetributionForeverRepeater);

            BT_PARALLEL_SELECTOR* pRetributiveAttackAndWait = new BT_PARALLEL_SELECTOR("RetributiveAttackAndWait", pIsUnderAttack, 2); //FIXME

            BT_ACTION_WAIT* pRetributionWait = new BT_ACTION_WAIT("WaitForResponse", pRetributiveAttackAndWait, 2);
            UNIT_ACTION_RETRIBUTIVE_ATTACK* pRetribution = new UNIT_ACTION_RETRIBUTIVE_ATTACK("RetributiveAttack", pRetributiveAttackAndWait);


    /*
    //Build Missile Turret (BUG)
    BT_DECO_REPEATER* pBuildMissileTurretForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildMissileTurret", pParallelSeq, 0, true, false, false);
    BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughMissileTurret = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughMissileTurret", pBuildMissileTurretForeverRepeater);
    SCV_ACTION_BUILD_MISSILE_TURRET* pBuildMissileTurret = new SCV_ACTION_BUILD_MISSILE_TURRET("BuildMissileTurret", pNotEnoughMissileTurret);
    */
}

// Called when the bot starts!
void StarterBot::onStart()
{
    // Set our BWAPI options here    
    BWAPI::Broodwar->setLocalSpeed(1);
    BWAPI::Broodwar->setFrameSkip(0);

    // Enable the flag that tells BWAPI top let users enter input while bot plays
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

    // Call MapTools OnStart
    m_mapTools.onStart();

    //Bwem
    BWEM::Map::Instance().Initialize(BWAPI::BroodwarPtr);

}

// Called on each frame of the game
void StarterBot::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();

    pData->currMinerals = BWAPI::Broodwar->self()->minerals();
    pData->currSupply = Tools::GetUnusedSupply(true);

    // AI BT
    if (pBT != nullptr && pBT->Evaluate(pData) != BT_NODE::RUNNING)
    {

        delete (BT_DECORATOR*)pBT;
        pBT = nullptr;
    }

    /*
    //Test BT
    if (pBtTest != nullptr && pBtTest->Evaluate(pData) != BT_NODE::RUNNING)
    {
        delete (BT_DECORATOR*)pBtTest;
        pBtTest = nullptr;
    }
    */

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();

    //BlackBoard Update
        //Barracks
        if (BWAPI::Broodwar->elapsedTime() <= EARLY_GAME)
        {
            pData->nWantedBarracksTotal = 1;
            pData->nWantedFactoryTotal = 1;
            pData->nWantedStarportTotal = 1;
        }
        else if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
        {
            pData->nWantedBarracksTotal = 3;
            pData->nWantedFactoryTotal = 2;
            pData->nWantedStarportTotal = 1;
        }
        else
        {
            pData->nWantedBarracksTotal = 5;
            pData->nWantedFactoryTotal = 4;
            pData->nWantedStarportTotal = 3;
        }

        //Supply Depot
        if (BWAPI::Broodwar->elapsedTime() >= EARLY_GAME) {
            int numBarracks = 0;
            int numFactories = 0;
            int numStarPorts = 0;

            for (auto& unit : BWAPI::Broodwar->self()->getUnits())
            {
                // if the unit is of the correct type, and it actually has been constructed, return it
                if (unit->getType() == BWAPI::UnitTypes::Terran_Barracks && unit->isCompleted()) {
                    numBarracks += 1;
                }
                else if (unit->getType() == BWAPI::UnitTypes::Terran_Factory && unit->isCompleted()) {
                    numFactories += 1;
                }
                else if (unit->getType() == BWAPI::UnitTypes::Terran_Starport && unit->isCompleted()) {
                    numStarPorts += 1;
                }
            }
            pData->thresholdSupply = int(BARRACKS_FACTOR * numBarracks + FACTORY_FACTOR * numFactories + STARPORT_FACTOR * numStarPorts);
        }

        // Update the available geysers around the command center
            // Get Geysers near the Command Centers and see if it has a Refinery
            // Get all player units
            BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();
            std::unordered_set<BWAPI::Unit> availableGeysers;
            for (auto& unit : unitSet)
            {
                if (unit->getType() == BWAPI::UnitTypes::Terran_Command_Center)
                {
                    BWAPI::Unitset temp = unit->getUnitsInRadius(128, BWAPI::Filter::IsResourceContainer);
                    if (!temp.empty())
                    {
                        for (auto& resource : temp) {
                            if (resource->getType() == BWAPI::UnitTypes::Resource_Vespene_Geyser)
                            {
                                availableGeysers.insert(resource);
                            }
                        }
                    }
                }

                if (unit->getType() == BWAPI::UnitTypes::Terran_Refinery)
                {

                }
            }

            pData->availableGeysers = availableGeysers;
        
    
}
/*

// Send our idle workers to mine minerals so they don't just stand there
void StarterBot::sendIdleWorkersToMinerals()
{
    // Let's send all of our starting workers to the closest mineral to them
    // First we need to loop over all of the units that we (BWAPI::Broodwar->self()) own
    const BWAPI::Unitset& myUnits = BWAPI::Broodwar->self()->getUnits();
    for (auto& unit : myUnits)
    {
        // Check the unit type, if it is an idle worker, then we want to send it somewhere
        if (unit->getType().isWorker() && unit->isIdle())
        {
            // Get the closest mineral to this worker unit
            BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());

            // If a valid mineral was found, right click it with the unit in order to start harvesting
            if (closestMineral) { unit->rightClick(closestMineral); }
        }
    }
}

// Train more workers so we can gather more income
void StarterBot::trainAdditionalWorkers()
{
    const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
    const int workersWanted = 20;
    const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits());
    if (workersOwned < workersWanted)
    {
        // get the unit pointer to my depot
        const BWAPI::Unit myDepot = Tools::GetDepot();

        // if we have a valid depot unit and it's currently not training something, train a worker
        // there is no reason for a bot to ever use the unit queueing system, it just wastes resources
        if (myDepot && !myDepot->isTraining()) { myDepot->train(workerType); }
    }
}

// Build more supply if we are going to run out soon
void StarterBot::buildAdditionalSupply()
{
    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

    // If we have a sufficient amount of supply, we don't need to do anything
    if (unusedSupply >= 2) { return; }

    // Otherwise, we are going to build a supply provider
    const BWAPI::UnitType supplyProviderType = BWAPI::Broodwar->self()->getRace().getSupplyProvider();

    const bool startedBuilding = Tools::BuildBuilding(supplyProviderType);
    if (startedBuilding)
    {
        BWAPI::Broodwar->printf("Started Building %s", supplyProviderType.getName().c_str());
    }
}

*/

// Draw some relevent information to the screen to help us debug the bot
void StarterBot::drawDebugInformation()
{
    BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), "Hello, World!\n");
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever the game ends and tells you if you won or not
void StarterBot::onEnd(bool isWinner)
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";
}

// Called whenever a unit is destroyed, with a pointer to the unit
void StarterBot::onUnitDestroy(BWAPI::Unit unit)
{
    //if the unit is farming then remove it from data structure
    for (int i = 0; i < pData->unitsFarmingMinerals.size(); i++)
    {
        if (pData->unitsFarmingMinerals[i].contains(unit)) pData->unitsFarmingMinerals[i].erase(unit);
    }
    for (int j = 0; j < pData->unitsFarmingMinerals.size(); j++)
    {
        if (pData->unitsFarmingGeysers[j].contains(unit)) pData->unitsFarmingGeysers[j].erase(unit);
    }

    //if the unit is a command center
    if (unit->getType() == BWAPI::UnitTypes::Terran_Command_Center)
    {
        for (int idx = 0; idx < pData->CommandCenters.size(); idx++)
        {
            if (pData->CommandCenters[idx] == unit) //FIXME
            {
                pData->CommandCenters.erase(pData->CommandCenters.begin() + idx);
                pData->tilePositionCommandCenters.erase(pData->tilePositionCommandCenters.begin() + idx);
                pData->positionCommandCenters.erase(pData->positionCommandCenters.begin() + idx);
                pData->unitsFarmingMinerals.erase(pData->unitsFarmingMinerals.begin() + idx);
                pData->unitsFarmingGeysers.erase(pData->unitsFarmingGeysers.begin() + idx);
            }
        }
    }

    // if (pData->unitsFarmingMinerals.contains(unit)) pData->unitsFarmingMinerals.erase(unit);
    // if (pData->unitsFarmingGeysers.contains(unit)) pData->unitsFarmingGeysers.erase(unit);
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void StarterBot::onUnitMorph(BWAPI::Unit unit)
{

}

// Called whenever a text is sent to the game by a user
void StarterBot::onSendText(std::string text)
{
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void StarterBot::onUnitCreate(BWAPI::Unit unit)
{

}

// Called whenever a unit finished construction, with a pointer to the unit
void StarterBot::onUnitComplete(BWAPI::Unit unit)
{

}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void StarterBot::onUnitShow(BWAPI::Unit unit)
{

}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void StarterBot::onUnitHide(BWAPI::Unit unit)
{

}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void StarterBot::onUnitRenegade(BWAPI::Unit unit)
{

}