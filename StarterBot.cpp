#include "StarterBot.h"
#include "Tools.h"
#include "MapTools.h"
#include <Data.h>
#include <format>

#include "BT.h"


StarterBot::StarterBot()
{
    pData = new Data();

    // Get Map Size
    pData->mapWidth = BWAPI::Broodwar->mapWidth();
    pData->mapHeight = BWAPI::Broodwar->mapHeight();

    if (pData->mapWidth >= pData->mapHeight)
    {
        pData->maxAggroDistance = 32 * pData->mapWidth / 2;
    }
    else
    {
        pData->maxAggroDistance = 32 * pData->mapHeight / 2;
    }

    // Get enemy spawn location
    auto& startLocations = BWAPI::Broodwar->getStartLocations();
    for (BWAPI::TilePosition tp : startLocations)
    {
        if (BWAPI::Broodwar->isExplored(tp))
        {
            continue;
        }

        BWAPI::Position enemySpawn(tp);
        pData->enemySpawnLocation = enemySpawn;
    }

    // initalize the list to keep the workers to each command center
    BWAPI::Unitset command_center_mineralsFarmer_list;
    pData->unitsFarmingMinerals.push_back(command_center_mineralsFarmer_list);
    BWAPI::Unitset command_center_geysersFarmer_list;
    pData->unitsFarmingGeysers.push_back(command_center_geysersFarmer_list);

    unsigned int nWWFM = 18;
    pData->nWantedWorkersFarmingMinerals.push_back(nWWFM);
    unsigned int nWWFG = 3;
    pData->nWantedWorkersFarmingGeysers.push_back(nWWFG);
    unsigned int nWWT = nWWFM + nWWFG;
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

            break;
        }
    }

    // Set initial rally point
    pData->rallyPoint = BWAPI::Broodwar->getBuildLocation(BWAPI::UnitTypes::Terran_Bunker, pData->tilePositionCommandCenters[0], 64, false);

    // Initializing data
    pData->currMinerals = 0;
    pData->currSupply = 0;
    pData->thresholdSupply = 10;

    pData->not_underattack_counter = 0;
    pData->pre_underattack = false;
    pData->now_underattack = false;
    pData->at_war = true;

    //pBtTest = nullptr;
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
    //pBtTest = new BT_DECORATOR("EntryPoint", nullptr);
    //BT_DECO_REPEATER * pForeverRepeater = new BT_DECO_REPEATER("RepeatForever", pBtTest, 0, true, false, true);
    //BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer", pForeverRepeater, 2);
    //BT_COND_GREATER_THAN<int> *pGreaterThan = new BT_COND_GREATER_THAN<int>("MineralsGreaterThanThreshold1",pSequencer,100, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pSequencer, std::format("current minerals greater than {}", 100));
    //BT_COND_LESSER_THAN<int>* pLesserThan = new BT_COND_LESSER_THAN<int>("MineralsLesserThanThreshold1", pSequencer, 100, pData->currMinerals, false);
    //BT_ACTION_LOG* pLog = new BT_ACTION_LOG("LogMSG", pSequencer, std::format("current minerals lesser than {}", 100));



    // Starcraft AI BT
    pBT = new BT_DECORATOR("EntryPoint", nullptr);

    //Main Parrallel Sequence
    BT_PARALLEL_SEQUENCER* pParallelSeq = new BT_PARALLEL_SEQUENCER("MainParallelSequence", pBT, 50);

        //--------------------------------------------------------------Global--------------------------------------------------------------//
        //For all Units:
        
        BT_DECO_REPEATER* pAttackForeverRepeater = new BT_DECO_REPEATER("RepeatForeverAttack", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pAttackSelector = new BT_SELECTOR("AttackSequencer", pAttackForeverRepeater, 3);

        //Search & Eliminate
        //UNIT_ACTION_SEARCHSIDES* pSearchAndEliminate = new UNIT_ACTION_SEARCHSIDES("RetributiveAttack", pAttackSelector);

        //Retributive Attack
        GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK* pIsUnderAttack = new GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK("WeAreUnderAttack", pAttackSelector);
        UNIT_ACTION_RETRIBUTIVE_ATTACK* pRetribution = new UNIT_ACTION_RETRIBUTIVE_ATTACK("RetributiveAttack", pIsUnderAttack);

        //Counter-Attack
        UNIT_DECO_CONDITION_GO_COUNTER_ATTACK* pGoCounterAttack = new UNIT_DECO_CONDITION_GO_COUNTER_ATTACK("goCounterAttack", pAttackSelector);
        UNIT_ACTION_COUNTER_ATTACK* pCounterAttack = new UNIT_ACTION_COUNTER_ATTACK("RetributiveAttack", pGoCounterAttack);



        //-------------------------------------------------------------Building-------------------------------------------------------------//
        
        //Command Center
        
        BT_DECO_REPEATER* pCommandCenterActionsForeverRepeater = new BT_DECO_REPEATER("CommandCenterActionsForeverRepeater", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectCommandCenterAcion = new BT_SELECTOR("SelectCommandCenterAcion", pCommandCenterActionsForeverRepeater, 3);

            //Train Worker
            BT_DECO_CONDITION_NOT_ENOUGH_WORKERS* pNotEnoughWorkers = new BT_DECO_CONDITION_NOT_ENOUGH_WORKERS("NotEnoughWorkers", pSelectCommandCenterAcion);
            CC_ACTION_TRAIN_WORKER* pTrainWorker = new CC_ACTION_TRAIN_WORKER("TrainWorker", pNotEnoughWorkers);

            //Build ComsatStation
            CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION* pNotEnoughComsatStation = new CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION("NotEnoughComsatStation", pSelectCommandCenterAcion);
            CC_ACTION_BUILD_COMSATSTATION* pBuildComsatStation = new CC_ACTION_BUILD_COMSATSTATION("BuildComsatStation", pNotEnoughComsatStation);

        //CC add-on: Comsat Station
        //Use ability: scanner sweep
        BT_DECO_REPEATER* pComsatStationScannerSweepForeverRepeater = new BT_DECO_REPEATER("ComsatStationScannerSweepForeverRepeater", pParallelSeq, 0, true, false, true);
        BT_SEQUENCER* pScanAndWait = new BT_SEQUENCER("ScanAndWait", pComsatStationScannerSweepForeverRepeater, 2);

            BT_ACTION_WAIT* pScanWait = new BT_ACTION_WAIT("WaitForResponse", pScanAndWait, 3);
            CS_ACTION_USE_ABILITY_SCANNERSWEEP* pUseScannerSweep = new CS_ACTION_USE_ABILITY_SCANNERSWEEP("UseScannerSweep", pScanAndWait);

        //Barracks
        BT_DECO_REPEATER* pBarracksTrainingForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBarracksTraining", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectBarracksUnit = new BT_SELECTOR("SelectBarracksUnit", pBarracksTrainingForeverRepeater, 4);
        
            //Train Ghost
            BA_DECO_CONDITION_NOT_ENOUGH_GHOST* pNotEnoughGhost = new BA_DECO_CONDITION_NOT_ENOUGH_GHOST("NotEnoughGhost", pSelectBarracksUnit);
            BA_ACTION_TRAIN_GHOST* pTrainGhost = new BA_ACTION_TRAIN_GHOST("TrainGhost", pNotEnoughGhost);

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
        BT_DECO_REPEATER* pFactoryActionForeverRepeater = new BT_DECO_REPEATER("RepeatForeverFactoryAction", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectFactoryAction = new BT_SELECTOR("SelectFactoryAction", pFactoryActionForeverRepeater, 4);

            //Build MachineShop
            FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP* pNotEnoughMachineShop = new FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP("NotEnoughMachineShop", pSelectFactoryAction);
            FA_ACTION_BUILD_MACHINESHOP* pBuildMachineShop = new FA_ACTION_BUILD_MACHINESHOP("BuildMachineShop", pNotEnoughMachineShop);

            //Train Goliath
            FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH* pNotEnoughGoliath = new FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH("NotEnoughGoliath", pSelectFactoryAction);
            FA_ACTION_TRAIN_GOLIATH* pTrainGoliath = new FA_ACTION_TRAIN_GOLIATH("TrainGoliath", pNotEnoughGoliath);

            //Train Siege Tank
            FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK* pNotEnoughSiegeTank = new FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK("NotEnoughSiegeTank", pSelectFactoryAction);
            FA_ACTION_TRAIN_SIEGETANK* pTrainSiegeTank = new FA_ACTION_TRAIN_SIEGETANK("TrainSiegeTank", pNotEnoughSiegeTank);

            //Train Vulture
            FA_DECO_CONDITION_NOT_ENOUGH_VULTURE* pNotEnoughVulture = new FA_DECO_CONDITION_NOT_ENOUGH_VULTURE("NotEnoughVulture", pSelectFactoryAction);
            FA_ACTION_TRAIN_VULTURE* pTrainVulture = new FA_ACTION_TRAIN_VULTURE("TrainVulture", pNotEnoughVulture);

        //Starport
        BT_DECO_REPEATER* pStarportActionForeverRepeater = new BT_DECO_REPEATER("RepeatForeverStarportAction", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectStarportAction = new BT_SELECTOR("SelectStarportAction", pStarportActionForeverRepeater, 6);

            //Build ControlTower
            SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER* pNotEnoughControlTower = new SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER("NotEnoughControlTower", pSelectStarportAction);
            SP_ACTION_BUILD_CONTROLTOWER* pBuildControlTower = new SP_ACTION_BUILD_CONTROLTOWER("BuildControlTower", pNotEnoughControlTower);

            //Train Battlecruiser
            SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER* pNotEnoughBattlecruiser = new SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER("NotEnoughBattlecruiser", pSelectStarportAction);
            SP_ACTION_TRAIN_BATTLECRUISER* pTrainBattlecruiser = new SP_ACTION_TRAIN_BATTLECRUISER("TrainBattlecruiser", pNotEnoughBattlecruiser);

            //Train Science Vessel
            SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL* pNotEnoughScienceVessel = new SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL("NotEnoughScienceVessel", pSelectStarportAction);
            SP_ACTION_TRAIN_SCIENCEVESSEL* pTrainScienceVessel = new SP_ACTION_TRAIN_SCIENCEVESSEL("TrainScienceVessel", pNotEnoughScienceVessel);

            //Train Valkyrie
            SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE* pNotEnoughValkyrie = new SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE("NotEnoughValkyrie", pSelectStarportAction);
            SP_ACTION_TRAIN_VALKYRIE* pTrainValkyrie = new SP_ACTION_TRAIN_VALKYRIE("TrainValkyrie", pNotEnoughValkyrie);

            //Train Dropship

            //Train Wraith
            SP_DECO_CONDITION_NOT_ENOUGH_WRAITH* pNotEnoughWraith = new SP_DECO_CONDITION_NOT_ENOUGH_WRAITH("NotEnoughWraith", pSelectStarportAction);
            SP_ACTION_TRAIN_WRAITH* pTrainWraith = new SP_ACTION_TRAIN_WRAITH("TrainWraith", pNotEnoughWraith);

        //Science Facility
        BT_DECO_REPEATER* pScienceFacilityActionForeverRepeater = new BT_DECO_REPEATER("RepeatForeverScienceFacilityAction", pParallelSeq, 0, true, false, true);
        BT_SELECTOR* pSelectScienceFacilityAction = new BT_SELECTOR("SelectScienceFacilityAction", pScienceFacilityActionForeverRepeater, 5);

            //Build CovertOps
            SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS* pNotEnoughCovertOps = new SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS("NotEnoughCovertOps", pSelectScienceFacilityAction);
            SF_ACTION_BUILD_COVERTOPS* pBuildCovertOps = new SF_ACTION_BUILD_COVERTOPS("BuildControlTower", pNotEnoughCovertOps);

            //Build PhysicsLab
            SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB* pNotEnoughPhysicsLab = new SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB("NotEnoughControlTower", pSelectScienceFacilityAction);
            SF_ACTION_BUILD_PHYSICSLAB* pBuildPhysicsLab = new SF_ACTION_BUILD_PHYSICSLAB("BuildControlTower", pNotEnoughPhysicsLab);

        //---------------------------------------------------------------Unit---------------------------------------------------------------//
        
        //SCV
        // Early-game Scouting
        BT_DECO_UNTIL_SUCCESS* pTryScoutingUntilSuccess = new BT_DECO_UNTIL_SUCCESS("TryScoutingUntilSuccess", pParallelSeq);
        SCV_DECO_CONDITION_EARLY_GAME_SCOUTING* pEarlyGameScouting = new SCV_DECO_CONDITION_EARLY_GAME_SCOUTING("EarlyGameScouting", pTryScoutingUntilSuccess);
        SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT* pSendIdleWorkerToScout = new SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT("SendIdleWorkerToScout", pEarlyGameScouting);

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
        
            //Build Unfinished Building
            BT_DECO_REPEATER* pBuildUnfinishedBuildingForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildUnfinishedBuilding", pParallelSeq, 0, true, false, true);
            BT_SEQUENCER* pBuildUnfinishedBuildingAndWait = new BT_SEQUENCER("BuildUnfinishedBuildingAndWait", pBuildUnfinishedBuildingForeverRepeater, 2);

                BT_ACTION_WAIT* pUnfinishedBuildingWait = new BT_ACTION_WAIT("WaitForResponse", pBuildUnfinishedBuildingAndWait, 3);
                SCV_ACTION_BUILD_UNFINISHED_BUILDING* pBuildUnfinishedBuilding = new SCV_ACTION_BUILD_UNFINISHED_BUILDING("BuildUnfinishedBuilding", pBuildUnfinishedBuildingAndWait);

            //Build Supply Provider
            BT_DECO_REPEATER* pBuildSupplyProviderForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildSupplyProvider", pParallelSeq, 0, true, false, false);
            BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughSupply = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughSupply", pBuildSupplyProviderForeverRepeater);

                //BT_SEQUENCER* pBuildSupplyAndWait = new BT_SEQUENCER("BuildSupplyAndWait", pNotEnoughSupply, 2);

                //BT_ACTION_WAIT* pSupplyWait = new BT_ACTION_WAIT("WaitForResponse", pBuildSupplyAndWait, 1);
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

            //Build Science Facility
            BT_DECO_REPEATER* pBuildScienceFacilityForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildScienceFacility", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY* pNotEnoughScienceFacility = new SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY("NotEnoughScienceFacility", pBuildScienceFacilityForeverRepeater);

                BT_SEQUENCER* pBuildScienceFacilityAndWait = new BT_SEQUENCER("BuildScienceFacilityAndWait", pNotEnoughScienceFacility, 2);

                BT_ACTION_WAIT* pScienceFacilityWait = new BT_ACTION_WAIT("WaitForResponse", pBuildScienceFacilityAndWait, 3);
                SCV_ACTION_BUILD_SCIENCEFACILITY* pBuildScienceFacility = new SCV_ACTION_BUILD_SCIENCEFACILITY("BuildScienceFacility", pBuildScienceFacilityAndWait);

            //Build Engineering Bay
            BT_DECO_REPEATER* pBuildeBayForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildeBay", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY* pNotEnougheBay = new SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY("NotEnougheBay", pBuildeBayForeverRepeater);

                BT_SEQUENCER* pBuildeBayAndWait = new BT_SEQUENCER("BuildeBayAndWait", pNotEnougheBay, 2);

                BT_ACTION_WAIT* peBayWait = new BT_ACTION_WAIT("WaitForResponse", pBuildeBayAndWait, 3);
                SCV_ACTION_BUILD_ENGINEERINGBAY* pBuildeBay = new SCV_ACTION_BUILD_ENGINEERINGBAY("BuildeBay", pBuildeBayAndWait);

            //Build Armory
            BT_DECO_REPEATER* pBuildArmoryForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildArmory", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY* pNotEnoughArmory = new SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY("NotEnoughArmory", pBuildArmoryForeverRepeater);

                BT_PARALLEL_SELECTOR* pBuildArmoryAndWait = new BT_PARALLEL_SELECTOR("BuildArmoryAndWait", pNotEnoughArmory, 2);

                BT_ACTION_WAIT* pArmoryWait = new BT_ACTION_WAIT("WaitForResponse", pBuildArmoryAndWait, 3);
                SCV_ACTION_BUILD_ARMORY* pBuildArmory = new SCV_ACTION_BUILD_ARMORY("BuildArmory", pBuildArmoryAndWait);

            //Build Bunker

            //Build Missile Turret(BUG)
            //BT_DECO_REPEATER* pBuildMissileTurretForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildMissileTurret", pParallelSeq, 0, true, false, false);
            //BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY* pNotEnoughMissileTurret = new BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY("NotEnoughMissileTurret", pBuildMissileTurretForeverRepeater);
            //SCV_ACTION_BUILD_MISSILE_TURRET* pBuildMissileTurret = new SCV_ACTION_BUILD_MISSILE_TURRET("BuildMissileTurret", pNotEnoughMissileTurret);

            //Build Command Center
            BT_DECO_REPEATER* pBuildCommandCenterForeverRepeater = new BT_DECO_REPEATER("RepeatForeverBuildCommandCenter", pParallelSeq, 0, true, false, true);
            SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER* pNotEnoughCommandCenter = new SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER("NotEnoughCommandCenter", pBuildCommandCenterForeverRepeater);

                BT_SEQUENCER* pBuildCommandCenterAndWait = new BT_SEQUENCER("BuildCommandCenterAndWait", pNotEnoughCommandCenter, 2);

                BT_ACTION_WAIT* pCommandCenterWait = new BT_ACTION_WAIT("WaitForResponse", pBuildCommandCenterAndWait, 6);
                SCV_ACTION_BUILD_COMMANDCENTER* pBuildCommandCenter = new SCV_ACTION_BUILD_COMMANDCENTER("BuildCommandCenter", pBuildCommandCenterAndWait);
           
            //---------------------------------------------------------------Tech---------------------------------------------------------------//

            BT_DECO_REPEATER* pAcademyResearch = new BT_DECO_REPEATER("RepeatForeverAcademyResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckAcademyResearch = new BT_SELECTOR("CheckAcademyResearch", pAcademyResearch, 5);

            AC_DECO_CONDITION_RESEARCH_STIMPACKTECH* pStimopacktechCanResearch = new AC_DECO_CONDITION_RESEARCH_STIMPACKTECH("StimopacktechCanResearch", pCheckAcademyResearch);
            AC_ACTION_RESEARCH_STIMPACKTECH* pStimopacktechResearch = new AC_ACTION_RESEARCH_STIMPACKTECH("StimopacktechResearch", pStimopacktechCanResearch);

            AC_DECO_CONDITION_RESEARCH_U238SHELLS* pU238shellsCanResearch = new AC_DECO_CONDITION_RESEARCH_U238SHELLS("U238shellsCanResearch", pCheckAcademyResearch);
            AC_ACTION_RESEARCH_U238SHELLS* pU238shellsResearch = new AC_ACTION_RESEARCH_U238SHELLS("U238shellsResearch", pU238shellsCanResearch);

            AC_DECO_CONDITION_RESEARCH_RESTORATION* pRestorationCanResearch = new AC_DECO_CONDITION_RESEARCH_RESTORATION("RestorationCanResearch", pCheckAcademyResearch);
            AC_ACTION_RESEARCH_RESTORATION* pRestorationResearch = new AC_ACTION_RESEARCH_RESTORATION("RestorationResearch", pRestorationCanResearch);

            AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR* pCaduceusreactorCanResearch = new AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR("CaduceusreactorCanResearch", pCheckAcademyResearch);
            AC_ACTION_RESEARCH_CADUCEUSREACTOR* pCaduceusreactorResearch = new AC_ACTION_RESEARCH_CADUCEUSREACTOR("CaduceusreactorResearch", pCaduceusreactorCanResearch);

            AC_DECO_CONDITION_RESEARCH_OPTICFLARE* pOpticflareCanResearch = new AC_DECO_CONDITION_RESEARCH_OPTICFLARE("OpticflareCanResearch", pCheckAcademyResearch);
            AC_ACTION_RESEARCH_OPTICFLARE* pOpticflareResearch = new AC_ACTION_RESEARCH_OPTICFLARE("OpticflareResearch", pOpticflareCanResearch);

            BT_DECO_REPEATER* pArmoryResearch = new BT_DECO_REPEATER("RepeatForeverArmoryResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckArmoryResearch = new BT_SELECTOR("CheckArmoryResearch", pArmoryResearch, 12);

            AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1* pVehicleweaponslv1CanResearch = new AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1("Vehicleweaponslv1CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV1* pVehicleweaponslv1Research = new AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV1("Vehicleweaponslv1Research", pVehicleweaponslv1CanResearch);
            AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2* pVehicleweaponslv2CanResearch = new AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2("Vehicleweaponslv2CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV2* pVehicleweaponslv2Research = new AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV2("Vehicleweaponslv2Research", pVehicleweaponslv2CanResearch);
            AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV3* pVehicleweaponslv3CanResearch = new AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV3("Vehicleweaponslv3CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV3* pVehicleweaponslv3Research = new AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV3("Vehicleweaponslv3Research", pVehicleweaponslv3CanResearch);

            AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV1* pShipweaponslv1CanResearch = new AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV1("Shipweaponslv1CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_SHIPWEAPONS_LV1* pShipweaponslv1Research = new AR_ACTION_UPGRADE_SHIPWEAPONS_LV1("Shipweaponslv1Research", pShipweaponslv1CanResearch);
            AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV2* pShipweaponslv2CanResearch = new AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV2("Shipweaponslv2CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_SHIPWEAPONS_LV2* pShipweaponslv2Research = new AR_ACTION_UPGRADE_SHIPWEAPONS_LV2("Shipweaponslv2Research", pShipweaponslv2CanResearch);
            AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3* pShipweaponslv3CanResearch = new AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3("Shipweaponslv3CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_SHIPWEAPONS_LV3* pShipweaponslv3Research = new AR_ACTION_UPGRADE_SHIPWEAPONS_LV3("Shipweaponslv3Research", pShipweaponslv3CanResearch);

            AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV1* pVehiclearmorlv1CanResearch = new AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV1("Vehiclearmorlv1CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_VEHICLEARMOR_LV1* pVehiclearmorlv1Research = new AR_ACTION_UPGRADE_VEHICLEARMOR_LV1("Vehiclearmorlv1Research", pVehiclearmorlv1CanResearch);
            AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV2* pVehiclearmorlv2CanResearch = new AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV2("Vehiclearmorlv2CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_VEHICLEARMOR_LV2* pVehiclearmorlv2Research = new AR_ACTION_UPGRADE_VEHICLEARMOR_LV2("Vehiclearmorlv2Research", pVehiclearmorlv2CanResearch);
            AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV3* pVehiclearmorlv3CanResearch = new AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV3("Vehiclearmorlv3CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_VEHICLEARMOR_LV3* pVehiclearmorlv3Research = new AR_ACTION_UPGRADE_VEHICLEARMOR_LV3("Vehiclearmorlv3Research", pVehiclearmorlv3CanResearch);

            AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1* pShiparmorlv1CanResearch = new AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1("Shiparmorlv1CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_SHIPARMOR_LV1* pShiparmorlv1Research = new AR_ACTION_UPGRADE_SHIPARMOR_LV1("Shiparmorlv1Research", pShiparmorlv1CanResearch);
            AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV2* pShiparmorlv2CanResearch = new AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV2("Shiparmorlv2CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_SHIPARMOR_LV2* pShiparmorlv2Research = new AR_ACTION_UPGRADE_SHIPARMOR_LV2("Shiparmorlv2Research", pShiparmorlv2CanResearch);
            AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV3* pShiparmorlv3CanResearch = new AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV3("Shiparmorlv3CanResearch", pCheckArmoryResearch);
            AR_ACTION_UPGRADE_SHIPARMOR_LV3* pShiparmorlv3Research = new AR_ACTION_UPGRADE_SHIPARMOR_LV3("Shiparmorlv3Research", pShiparmorlv3CanResearch);

            BT_DECO_REPEATER* pEngineeringbayResearch = new BT_DECO_REPEATER("RepeatForeverEngineeringbayResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckEngineeringbayResearch = new BT_SELECTOR("CheckEngineeringbayResearch", pEngineeringbayResearch, 6);

            EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV1* pInfantryweaponslv1CanResearch = new EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV1("Infantryweaponslv1CanResearch", pCheckEngineeringbayResearch);
            EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV1* pInfantryweaponslv1Research = new EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV1("Infantryweaponslv1Research", pInfantryweaponslv1CanResearch);
            EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV2* pInfantryweaponslv2CanResearch = new EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV2("Infantryweaponslv2CanResearch", pCheckEngineeringbayResearch);
            EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV2* pInfantryweaponslv2Research = new EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV2("Infantryweaponslv2Research", pInfantryweaponslv2CanResearch);
            EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3* pInfantryweaponslv3CanResearch = new EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3("Infantryweaponslv3CanResearch", pCheckEngineeringbayResearch);
            EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3* pInfantryweaponslv3Research = new EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3("Infantryweaponslv3Research", pInfantryweaponslv3CanResearch);

            EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1* pInfantryarmorlv1CanResearch = new EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1("Infantryarmorlv1CanResearch", pCheckEngineeringbayResearch);
            EB_ACTION_UPGRADE_INFANTRYARMOR_LV1* pInfantryarmorlv1Research = new EB_ACTION_UPGRADE_INFANTRYARMOR_LV1("Infantryarmorlv1Research", pInfantryarmorlv1CanResearch);
            EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2* pInfantryarmorlv2CanResearch = new EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2("Infantryarmorlv2CanResearch", pCheckEngineeringbayResearch);
            EB_ACTION_UPGRADE_INFANTRYARMOR_LV2* pInfantryarmorlv2Research = new EB_ACTION_UPGRADE_INFANTRYARMOR_LV2("Infantryarmorlv2Research", pInfantryarmorlv2CanResearch);
            EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV3* pInfantryarmorlv3CanResearch = new EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV3("Infantryarmorlv3CanResearch", pCheckEngineeringbayResearch);
            EB_ACTION_UPGRADE_INFANTRYARMOR_LV3* pInfantryarmorlv3Research = new EB_ACTION_UPGRADE_INFANTRYARMOR_LV3("Infantryarmorlv3Research", pInfantryarmorlv3CanResearch);

            BT_DECO_REPEATER* pMachineshopResearch = new BT_DECO_REPEATER("RepeatForeverMachineshopResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckMachineshopResearch = new BT_SELECTOR("CheckMachineshopResearch", pMachineshopResearch, 4);

            MS_DECO_CONDITION_RESEARCH_SIEGETECH* pSiegetechCanResearch = new MS_DECO_CONDITION_RESEARCH_SIEGETECH("SiegetechCanResearch", pCheckMachineshopResearch);
            MS_ACTION_RESEARCH_SIEGETECH* pSiegetechResearch = new MS_ACTION_RESEARCH_SIEGETECH("SiegetechResearch", pSiegetechCanResearch);

            /*
            MS_DECO_CONDITION_RESEARCH_SPIDERMINE* pSpidermineCanResearch = new MS_DECO_CONDITION_RESEARCH_SPIDERMINE("SpidermineCanResearch", pCheckMachineshopResearch);
            MS_ACTION_RESEARCH_SPIDERMINE* pSpidermineResearch = new MS_ACTION_RESEARCH_SPIDERMINE("SpidermineResearch", pSpidermineCanResearch);
            */

            MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS* pCharonboosterCanResearch = new MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS("CharonboosterCanResearch", pCheckMachineshopResearch);
            MS_ACTION_RESEARCH_CHARONBOOSTERS* pCharonboosterResearch = new MS_ACTION_RESEARCH_CHARONBOOSTERS("CharonboosterResearch", pCharonboosterCanResearch);

            MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS* pIonthrustersCanResearch = new MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS("IonthrustersCanResearch", pCheckMachineshopResearch);
            MS_ACTION_RESEARCH_IONTHRUSTERS* pIonthrustersResearch = new MS_ACTION_RESEARCH_IONTHRUSTERS("IonthrustersResearch", pIonthrustersCanResearch);

            BT_DECO_REPEATER* pSciencefacilityResearch = new BT_DECO_REPEATER("RepeatForeverSciencefacilityResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckSciencefacilityResearch = new BT_SELECTOR("CheckSciencefacilityResearch", pSciencefacilityResearch, 3);

            SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE* pEmpshockwaveCanResearch = new SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE("EmpshockwaveCanResearch", pCheckSciencefacilityResearch);
            SF_ACTION_RESEARCH_EMPSHOCKWAVE* pEmpshockwaveResearch = new SF_ACTION_RESEARCH_EMPSHOCKWAVE("EmpshockwaveResearch", pEmpshockwaveCanResearch);

            SF_DECO_CONDITION_RESEARCH_IRRADIATE* pIrradiateCanResearch = new SF_DECO_CONDITION_RESEARCH_IRRADIATE("IrradiateCanResearch", pCheckSciencefacilityResearch);
            SF_ACTION_RESEARCH_IRRADIATE* pIrradiateResearch = new SF_ACTION_RESEARCH_IRRADIATE("IrradiateResearch", pIrradiateCanResearch);

            SF_DECO_CONDITION_RESEARCH_TITANREACTOR* pTitanreactorCanResearch = new SF_DECO_CONDITION_RESEARCH_TITANREACTOR("TitanreactorCanResearch", pCheckSciencefacilityResearch);
            SF_ACTION_RESEARCH_TITANREACTOR* pTitanreactorResearch = new SF_ACTION_RESEARCH_TITANREACTOR("TitanreactorResearch", pTitanreactorCanResearch);

            BT_DECO_REPEATER* pCovertopsResearch = new BT_DECO_REPEATER("RepeatForeverCovertopsResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckCovertopsResearch = new BT_SELECTOR("CheckCovertopsResearch", pCovertopsResearch, 4);

            CO_DECO_CONDITION_RESEARCH_LOCKDOWN* pLockdownCanResearch = new CO_DECO_CONDITION_RESEARCH_LOCKDOWN("LockdownCanResearch", pCheckCovertopsResearch);
            CO_ACTION_RESEARCH_LOCKDOWN* pLockdownResearch = new CO_ACTION_RESEARCH_LOCKDOWN("LockdownResearch", pLockdownCanResearch);

            CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING* pPersonalcloakingCanResearch = new CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING("PersonalcloakingCanResearch", pCheckCovertopsResearch);
            CO_ACTION_RESEARCH_PERSONALCLOAKING* pPersonalcloakingResearch = new CO_ACTION_RESEARCH_PERSONALCLOAKING("PersonalcloakingResearch", pPersonalcloakingCanResearch);

            CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS* pOcularimplantsCanResearch = new CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS("OcularimplantsCanResearch", pCheckCovertopsResearch);
            CO_ACTION_RESEARCH_OCULARIMPLANTS* pOcularimplantsResearch = new CO_ACTION_RESEARCH_OCULARIMPLANTS("OcularimplantsResearch", pOcularimplantsCanResearch);

            CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR* pMoebiusreactorCanResearch = new CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR("MoebiusreactorCanResearch", pCheckCovertopsResearch);
            CO_ACTION_RESEARCH_MOEBIUSREACTOR* pMoebiusreactorResearch = new CO_ACTION_RESEARCH_MOEBIUSREACTOR("MoebiusreactorResearch", pMoebiusreactorCanResearch);

            BT_DECO_REPEATER* pPhysicslabResearch = new BT_DECO_REPEATER("RepeatForeverPhysicslabResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckPhysicslabResearch = new BT_SELECTOR("CheckPhysicslabResearch", pPhysicslabResearch, 2);

            PL_DECO_CONDITION_RESEARCH_YAMATOGUN* pYamatogunCanResearch = new PL_DECO_CONDITION_RESEARCH_YAMATOGUN("YamatogunCanResearch", pCheckPhysicslabResearch);
            PL_ACTION_RESEARCH_YAMATOGUN* pYamatogunResearch = new PL_ACTION_RESEARCH_YAMATOGUN("YamatogunResearch", pYamatogunCanResearch);

            PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR* pColossusreactorCanResearch = new PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR("ColossusreactorCanResearch", pCheckPhysicslabResearch);
            PL_ACTION_RESEARCH_COLOSSUSREACTOR* pColossusreactorResearch = new PL_ACTION_RESEARCH_COLOSSUSREACTOR("ColossusreactorResearch", pColossusreactorCanResearch);

            BT_DECO_REPEATER* pControltowerResearch = new BT_DECO_REPEATER("RepeatForeverControltowerResearch", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pCheckControltowerResearch = new BT_SELECTOR("CheckControltowerResearch", pControltowerResearch, 2);

            CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD* pCloakingfieldCanResearch = new CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD("CloakingfieldCanResearch", pCheckControltowerResearch);
            CT_ACTION_RESEARCH_CLOAKINGFIELD* pCloakingfieldResearch = new CT_ACTION_RESEARCH_CLOAKINGFIELD("CloakingfieldResearch", pCloakingfieldCanResearch);

            CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR* pApolloreactorCanResearch = new CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR("ApolloreactorCanResearch", pCheckControltowerResearch);
            CT_ACTION_RESEARCH_APOLLOREACTOR* pApolloreactorResearch = new CT_ACTION_RESEARCH_APOLLOREACTOR("ApolloreactorResearch", pApolloreactorCanResearch);

            //---------------------------------------------------------------Skill---------------------------------------------------------------//
            
            BT_DECO_REPEATER* pBCYamatogunForeverRepeater = new BT_DECO_REPEATER("BCYamatogunForeverRepeater", pParallelSeq, 0, true, false, true);

            BT_SEQUENCER* pBCYamatogunAndWait = new BT_SEQUENCER("BCYamatogunAndWait", pBCYamatogunForeverRepeater, 2);
            BT_ACTION_WAIT* pBCYamatogunWait = new BT_ACTION_WAIT("WaitForBCYamatogun", pBCYamatogunAndWait, 2);
            BC_ACTION_USE_ABILITY_YAMATOGUN* pUseBCYamatogun = new BC_ACTION_USE_ABILITY_YAMATOGUN("UseBCYamatogun", pBCYamatogunAndWait);
            /*
            BT_DECO_REPEATER* pDropshipForeverRepeater = new BT_DECO_REPEATER("DropshipForeverRepeater", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pSelectDropship = new BT_SELECTOR("SelectDropship", pDropshipForeverRepeater, 2);

            BT_SEQUENCER* pDSLoadAndWait = new BT_SEQUENCER("DSLoadAndWait", pSelectDropship, 2);
            BT_ACTION_WAIT* pDSLoadWait = new BT_ACTION_WAIT("WaitForDSLoad", pDSLoadAndWait, 2);
            DS_ACTION_USE_ABILITY_LOAD* pUseDSLoad = new DS_ACTION_USE_ABILITY_LOAD("UseDSLoad", pDSLoadAndWait);

            BT_SEQUENCER* pDSUnLoadAndWait = new BT_SEQUENCER("DSUnLoadAndWait", pSelectDropship, 2);
            BT_ACTION_WAIT* pDSUnLoadWait = new BT_ACTION_WAIT("WaitForDSUnLoad", pDSUnLoadAndWait, 2);
            DS_ACTION_USE_ABILITY_UNLOAD* pUseDSUnLoad = new DS_ACTION_USE_ABILITY_UNLOAD("UseDSUnLoad", pDSUnLoadAndWait);
            */
            BT_DECO_REPEATER* pFBStimpackForeverRepeater = new BT_DECO_REPEATER("FBStimpackForeverRepeater", pParallelSeq, 0, true, false, true);

            BT_SEQUENCER* pFBStimpackAndWait = new BT_SEQUENCER("FBStimpackAndWait", pFBStimpackForeverRepeater, 2);
            BT_ACTION_WAIT* pFBStimpackWait = new BT_ACTION_WAIT("WaitForFBStimpack", pFBStimpackAndWait, 3);
            FB_ACTION_USE_ABILITY_STIMPACK* pUseFBStimpack = new FB_ACTION_USE_ABILITY_STIMPACK("UseFBStimpack", pFBStimpackAndWait);

            BT_DECO_REPEATER* pGhostForeverRepeater = new BT_DECO_REPEATER("GhostForeverRepeater", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pSelectGhost = new BT_SELECTOR("SelectGhost", pGhostForeverRepeater, 4);

            BT_SEQUENCER* pGHCloakAndWait = new BT_SEQUENCER("GHCloakAndWait", pSelectGhost, 2);
            BT_ACTION_WAIT* pGHCloakWait = new BT_ACTION_WAIT("WaitForGHCloak", pGHCloakAndWait, 2);
            GH_ACTION_USE_ABILITY_CLOAK* pUseGHCloak = new GH_ACTION_USE_ABILITY_CLOAK("UseGHCloak", pGHCloakAndWait);

            BT_SEQUENCER* pGHLockdownAndWait = new BT_SEQUENCER("GHLockdownAndWait", pSelectGhost, 2);
            BT_ACTION_WAIT* pGHLockdownWait = new BT_ACTION_WAIT("WaitForGHLockdown", pGHLockdownAndWait, 2);
            GH_ACTION_USE_ABILITY_LOCKDOWN* pUseGHLockdown = new GH_ACTION_USE_ABILITY_LOCKDOWN("UseGHLockdown", pGHLockdownAndWait);

            BT_SEQUENCER* pGHNukeAndWait = new BT_SEQUENCER("GHNukeAndWait", pSelectGhost, 2);
            BT_ACTION_WAIT* pGHNukeWait = new BT_ACTION_WAIT("WaitForGHNuke", pGHNukeAndWait, 1);
            GH_ACTION_USE_ABILITY_NUKE* pUseGHNuke = new GH_ACTION_USE_ABILITY_NUKE("UseGHNuke", pGHNukeAndWait);

            BT_SEQUENCER* pGHUncloakAndWait = new BT_SEQUENCER("GHUncloakAndWait", pSelectGhost, 2);
            BT_ACTION_WAIT* pGHUncloakWait = new BT_ACTION_WAIT("WaitForGHUncloak", pGHUncloakAndWait, 2);
            GH_ACTION_USE_ABILITY_UNCLOAK* pUseGHUncloak = new GH_ACTION_USE_ABILITY_UNCLOAK("UseGHUncloak", pGHUncloakAndWait);
            
            BT_DECO_REPEATER* pMRStimpackForeverRepeater = new BT_DECO_REPEATER("MRStimpackForeverRepeater", pParallelSeq, 0, true, false, true);

            BT_SEQUENCER* pMRStimpackAndWait = new BT_SEQUENCER("MRStimpackAndWait", pMRStimpackForeverRepeater, 2);
            BT_ACTION_WAIT* pMRStimpackWait = new BT_ACTION_WAIT("WaitForMRStimpack", pMRStimpackAndWait, 3);
            MR_ACTION_USE_ABILITY_STIMPACK* pUseMRStimpack = new MR_ACTION_USE_ABILITY_STIMPACK("UseMRStimpack", pMRStimpackAndWait);

            BT_DECO_REPEATER* pMedicForeverRepeater = new BT_DECO_REPEATER("MedicForeverRepeater", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pSelectMedic = new BT_SELECTOR("SelectMedic", pMedicForeverRepeater, 2);

            BT_SEQUENCER* pMDOpticflareAndWait = new BT_SEQUENCER("MDOpticflareAndWait", pSelectMedic, 2);
            BT_ACTION_WAIT* pMDOpticflareWait = new BT_ACTION_WAIT("WaitForMDOpticflare", pMDOpticflareAndWait, 2);
            MD_ACTION_USE_ABILITY_OPTICFLARE* pUseMDOpticflare = new MD_ACTION_USE_ABILITY_OPTICFLARE("UseMDOpticflare", pMDOpticflareAndWait);

            BT_SEQUENCER* pMDRestorationAndWait = new BT_SEQUENCER("MDRestorationAndWait", pSelectMedic, 2);
            BT_ACTION_WAIT* pMDRestorationWait = new BT_ACTION_WAIT("WaitForMDRestoration", pMDRestorationAndWait, 2);
            MD_ACTION_USE_ABILITY_RESTORATION* pUseMDRestoration = new MD_ACTION_USE_ABILITY_RESTORATION("UseMDRestoration", pMDRestorationAndWait);
            
            BT_DECO_REPEATER* pScienceVesselForeverRepeater = new BT_DECO_REPEATER("ScienceVesselForeverRepeater", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pSelectScienceVessel = new BT_SELECTOR("SelectScienceVessel", pScienceVesselForeverRepeater, 3);

            BT_SEQUENCER* pSVDefensivematrixAndWait = new BT_SEQUENCER("SVDefensivematrixAndWait", pSelectScienceVessel, 2);
            BT_ACTION_WAIT* pSVDefensivematrixWait = new BT_ACTION_WAIT("WaitForSVDefensivematrix", pSVDefensivematrixAndWait, 2);
            SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX* pUseSVDefensivematrix = new SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX("UseSVDefensivematrix", pSVDefensivematrixAndWait);

            BT_SEQUENCER* pSVEmpshockwaveAndWait = new BT_SEQUENCER("SVEmpshockwaveAndWait", pSelectScienceVessel, 2);
            BT_ACTION_WAIT* pSVEmpshockwaveWait = new BT_ACTION_WAIT("WaitForSVEmpshockwave", pSVEmpshockwaveAndWait, 2);
            SV_ACTION_USE_ABILITY_EMPSHOCKWAVE* pUseSVEmpshockwave = new SV_ACTION_USE_ABILITY_EMPSHOCKWAVE("UseSVEmpshockwave", pSVEmpshockwaveAndWait);

            BT_SEQUENCER* pSVIrradiateAndWait = new BT_SEQUENCER("SVIrradiateAndWait", pSelectScienceVessel, 2);
            BT_ACTION_WAIT* pSVIrradiateWait = new BT_ACTION_WAIT("WaitForSVIrradiate", pSVIrradiateAndWait, 2);
            SV_ACTION_USE_ABILITY_IRRADIATE* pUseSVIrradiate = new SV_ACTION_USE_ABILITY_IRRADIATE("UseSVIrradiate", pSVIrradiateAndWait);
            /*
            BT_DECO_REPEATER* pSCVRepairForeverRepeater = new BT_DECO_REPEATER("SCVRepairForeverRepeater", pParallelSeq, 0, true, false, true);
            
            BT_SEQUENCER* pSCVRepairAndWait = new BT_SEQUENCER("SCVRepairAndWait", pSCVRepairForeverRepeater, 2);
            BT_ACTION_WAIT* pSCVRepairWait = new BT_ACTION_WAIT("WaitForSCVRepair", pSCVRepairAndWait, 2);
            SCV_ACTION_REPAIR* pUseSCVRepair = new SCV_ACTION_REPAIR("UseSCVRepair", pSCVRepairAndWait);
            */
            BT_DECO_REPEATER* pSiegeTankForeverRepeater = new BT_DECO_REPEATER("SiegeTankForeverRepeater", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pSelectSiegeTank = new BT_SELECTOR("SelectSiegeTank", pSiegeTankForeverRepeater, 2);
            
            BT_SEQUENCER* pSTSiegemodeAndWait = new BT_SEQUENCER("STSiegemodeAndWait", pSelectSiegeTank, 2);
            BT_ACTION_WAIT* pSTSiegemodeWait = new BT_ACTION_WAIT("WaitForSTSiegemode", pSTSiegemodeAndWait, 2);
            ST_ACTION_USE_ABILITY_SIEGEMODE* pUseSTSiegemode = new ST_ACTION_USE_ABILITY_SIEGEMODE("UseSTSiegemode", pSTSiegemodeAndWait);

            BT_SEQUENCER* pSTTankmodeAndWait = new BT_SEQUENCER("STTankmodeAndWait", pSelectSiegeTank, 2);
            BT_ACTION_WAIT* pSTTankmodeWait = new BT_ACTION_WAIT("WaitForSTTankmode", pSTTankmodeAndWait, 2);
            ST_ACTION_USE_ABILITY_TANKMODE* pUseSTTankmode = new ST_ACTION_USE_ABILITY_TANKMODE("UseSTTankmode", pSTTankmodeAndWait);
            
            BT_DECO_REPEATER* pVTSpidermineForeverRepeater = new BT_DECO_REPEATER("VTSpidermineForeverRepeater", pParallelSeq, 0, true, false, true);

            BT_SEQUENCER* pVTSpidermineAndWait = new BT_SEQUENCER("VTSpidermineAndWait", pVTSpidermineForeverRepeater, 2);
            BT_ACTION_WAIT* pVTSpidermineWait = new BT_ACTION_WAIT("WaitForVTSpidermine", pVTSpidermineAndWait, 2);
            VT_ACTION_USE_ABILITY_SPIDERMINE* pUseVTSpidermine = new VT_ACTION_USE_ABILITY_SPIDERMINE("UseVTSpidermine", pVTSpidermineAndWait);

            BT_DECO_REPEATER* pWraithForeverRepeater = new BT_DECO_REPEATER("WraithForeverRepeater", pParallelSeq, 0, true, false, true);
            BT_SELECTOR* pSelectWraith = new BT_SELECTOR("SelectWraith", pWraithForeverRepeater, 2);

            BT_SEQUENCER* pWRCloakAndWait = new BT_SEQUENCER("WRCloakAndWait", pSelectWraith, 2);
            BT_ACTION_WAIT* pWRCloakWait = new BT_ACTION_WAIT("WaitForWRCloak", pWRCloakAndWait, 2);
            WR_ACTION_USE_ABILITY_CLOAK* pUseWRCloak = new WR_ACTION_USE_ABILITY_CLOAK("UseWRCloak", pWRCloakAndWait);

            BT_SEQUENCER* pWRUncloakAndWait = new BT_SEQUENCER("WRUncloakAndWait", pSelectWraith, 2);
            BT_ACTION_WAIT* pWRUncloakWait = new BT_ACTION_WAIT("WaitForWRUncloak", pWRUncloakAndWait, 2);
            WR_ACTION_USE_ABILITY_UNCLOAK* pUseWRUncloak = new WR_ACTION_USE_ABILITY_UNCLOAK("UseWRUncloak", pWRUncloakAndWait);
            
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

        //Get all map areas
        const std::vector<BWEM::Area>& allAreas = BWEM::Map::Instance().Areas();

        //Get all expansion points & blocking minerals
        for (size_t i = 0; i < allAreas.size(); i++)
        {
            auto& temp_bases = allAreas[i].Bases();
            auto& temp_chokes = allAreas[i].ChokePoints();

            for (size_t j = 0; j < temp_bases.size(); j++)
            {
                auto& temp_location = temp_bases[j].Location();
                pData->tilesOfExpansions.push_back(temp_location);
            }

            for (auto& choke : temp_chokes)
            {
                if (choke->BlockingNeutral() != nullptr)
                {
                    if (choke->BlockingNeutral()->IsMineral())
                    {
                        pData->blockingMinerals.insert(choke->BlockingNeutral()->Unit());
                    }
                }
            }
        }

        //Sort all expansion points
        BWAPI::TilePosition temp;
        for (size_t i = 0; i < pData->tilesOfExpansions.size() - 1; i++)
            for (size_t j = 0; j < pData->tilesOfExpansions.size() - 1 - i; j++)
                if (pData->CommandCenters[0]->getDistance(BWAPI::Position(pData->tilesOfExpansions[j])) > 
                    pData->CommandCenters[0]->getDistance(BWAPI::Position(pData->tilesOfExpansions[j + 1]))) 
                {
                    temp = pData->tilesOfExpansions[j];
                    pData->tilesOfExpansions[j] = pData->tilesOfExpansions[j + 1];
                    pData->tilesOfExpansions[j + 1] = temp;
                }  
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
    BWAPI::Unitset unitSet = BWAPI::Broodwar->self()->getUnits();

        //Enemy race
        if (BWAPI::Broodwar->enemy()->getRace() != BWAPI::Races::Unknown)
        {
            pData->enemyRace = BWAPI::Broodwar->enemy()->getRace();
        }

        //Enemy main base
        if ((pData->enemyMainDestroyed == false) && (BWAPI::Broodwar->isVisible(BWAPI::TilePosition(pData->enemySpawnLocation))))
        {
            auto enemyHome = BWAPI::Broodwar->getUnitsOnTile(BWAPI::TilePosition(pData->enemySpawnLocation), BWAPI::Filter::IsEnemy);
            if (enemyHome.empty())
            {
                BWAPI::Broodwar->sendText("GG WP");
                pData->enemyMainDestroyed = true;
            }
        }

        //Game phase
        if (BWAPI::Broodwar->elapsedTime() <= EARLY_GAME)
        {
            pData->nWantedBarracksTotal = 1;
            pData->nWantedFactoryTotal = 1;
            pData->nWantedStarportTotal = 0;

            pData->nWantedScienceFacilityTotal = 0;
            pData->nWantedEngineeringBayTotal = 0;
            pData->nWantedArmoryTotal = 0;

            pData->nWantedCommandCenterForTheMoment = 3;

            pData->thresholdSupply = 10;
        }
        else if (BWAPI::Broodwar->elapsedTime() <= MID_GAME)
        {
            pData->nWantedBarracksTotal = 2;
            pData->nWantedFactoryTotal = 1;
            pData->nWantedStarportTotal = 1;

            pData->nWantedScienceFacilityTotal = 0;
            pData->nWantedEngineeringBayTotal = 1;
            pData->nWantedArmoryTotal = 0;

            pData->nWantedCommandCenterForTheMoment = 4;

            pData->thresholdSupply = 20;
        }
        else
        {
            pData->nWantedBarracksTotal = 4;
            pData->nWantedFactoryTotal = 3;
            pData->nWantedStarportTotal = 2;

            pData->nWantedScienceFacilityTotal = 2;
            pData->nWantedEngineeringBayTotal = 2;
            pData->nWantedArmoryTotal = 2;

            pData->thresholdSupply = 36;

            pData->nWantedCommandCenterForTheMoment = 6;
        }

        if (pData->enemyMainDestroyed)
        {
            pData->nWantedCommandCenterForTheMoment = pData->tilesOfExpansions.size();
            pData->maxAggroDistance = 65536;
        }

        //Infrastructures count
        unsigned int numBarracks = 0;
        unsigned int numFactories = 0;
        unsigned int numStarPorts = 0;

        for (auto& unit : unitSet)
        {
            // if the unit is of the correct type, and it actually has been constructed, return it
            if (unit->getType() == BWAPI::UnitTypes::Terran_Barracks && unit->isCompleted()) {
                numBarracks += 1;
                pData->infrastructures.insert(unit);
            }
            else if (unit->getType() == BWAPI::UnitTypes::Terran_Factory && unit->isCompleted()) {
                numFactories += 1;
                pData->infrastructures.insert(unit);
            }
            else if (unit->getType() == BWAPI::UnitTypes::Terran_Starport && unit->isCompleted()) {
                numStarPorts += 1;
                pData->infrastructures.insert(unit);
            }
        }
        
        // Update the available geysers around the command center
            // Get Geysers near the Command Centers and see if it has a Refinery
            std::unordered_set<BWAPI::Unit> availableGeysers;
            for (auto& unit : unitSet)
            {
                if (unit->getType() == BWAPI::UnitTypes::Terran_Command_Center)
                {
                    BWAPI::Unitset temp = unit->getUnitsInRadius(128, BWAPI::Filter::IsResourceContainer);
                    if (!temp.empty())
                    {
                        for (auto& resource : temp) 
                        {
                            if (resource->getType() == BWAPI::UnitTypes::Resource_Vespene_Geyser)
                            {
                                availableGeysers.insert(resource);
                            }
                        }
                    }
                }
            }

            pData->availableGeysers = availableGeysers;
        
    
        // Update battle situation
            // if the status changes from "under attack" to "not under attack" in this frame
            // reset the counter
            if (!pData->now_underattack && pData->pre_underattack)
            {
                pData->not_underattack_counter = 0;
            }
            // if the engagement has stopped
            // frame(time) counter
            if (!pData->now_underattack && !pData->pre_underattack)
            {
                pData->not_underattack_counter += 1;
            }

            // update
            pData->pre_underattack = pData->now_underattack;
       
        //If a unit get stuck
        pData->stuckUnits.clear();
        for (auto& unit : unitSet)
        {
            if (unit->isStuck())
            {
                pData->stuckUnits.insert(unit);
            }
        }
}

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
    if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
    {
        for (size_t i = 0; i < pData->unitsFarmingMinerals.size(); i++)
        {
            if (pData->unitsFarmingMinerals[i].contains(unit))
            {
                pData->unitsFarmingMinerals[i].erase(unit);
                break;
            }
        }
        for (size_t j = 0; j < pData->unitsFarmingGeysers.size(); j++)
        {
            if (pData->unitsFarmingGeysers[j].contains(unit))
            {
                pData->unitsFarmingGeysers[j].erase(unit);
                break;
            }
        }
    }

    //if the unit is a command center
    else if (unit->getType() == BWAPI::UnitTypes::Terran_Command_Center)
    {
        for (size_t idx = 0; idx < pData->CommandCenters.size(); idx++)
        {
            if (pData->CommandCenters[idx] == unit) //FIXME
            {
                pData->CommandCenters.erase(pData->CommandCenters.begin() + idx);
                pData->tilePositionCommandCenters.erase(pData->tilePositionCommandCenters.begin() + idx);
                pData->positionCommandCenters.erase(pData->positionCommandCenters.begin() + idx);
                pData->unitsFarmingMinerals.erase(pData->unitsFarmingMinerals.begin() + idx);
                pData->unitsFarmingGeysers.erase(pData->unitsFarmingGeysers.begin() + idx);

                pData->rallyPoint = BWAPI::Broodwar->getBuildLocation(BWAPI::UnitTypes::Terran_Bunker, BWAPI::Broodwar->self()->getStartLocation(), 64, false);
                break;
            }
        }
    }

    //if the unit is a scout
    if (pData->scoutUnits.size() && pData->scoutUnits.contains(unit))
    {
        pData->scoutUnits.erase(unit);
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

    if (unit->getPlayer() == BWAPI::Broodwar->self() && unit->getType() == BWAPI::UnitTypes::Terran_Command_Center && unit->isBeingConstructed())
    {
        pData->CommandCenters.push_back(unit);
        pData->tilePositionCommandCenters.push_back(unit->getTilePosition());
        pData->positionCommandCenters.push_back(unit->getPosition());

        BWAPI::Unitset command_center_mineralsFarmer_list;
        pData->unitsFarmingMinerals.push_back(command_center_mineralsFarmer_list);
        BWAPI::Unitset command_center_geysersFarmer_list;
        pData->unitsFarmingGeysers.push_back(command_center_geysersFarmer_list);

        unsigned int nWWFM = (unit->getUnitsInRadius(128, BWAPI::Filter::IsMineralField).size()) * 2;
        pData->nWantedWorkersFarmingMinerals.push_back(nWWFM);
        unsigned int nWWFG = (unit->getUnitsInRadius(128, BWAPI::Filter::IsResourceContainer && (!BWAPI::Filter::IsMineralField)).size()) * 3;
        pData->nWantedWorkersFarmingGeysers.push_back(nWWFG);
        unsigned int nWWT = nWWFM + nWWFG;
        pData->nWantedWorkersTotal.push_back(nWWT);

    }
}

// Called whenever a unit finished construction, with a pointer to the unit
void StarterBot::onUnitComplete(BWAPI::Unit unit)
{
    if (unit->getPlayer() == BWAPI::Broodwar->self() && unit->getType() == BWAPI::UnitTypes::Terran_Command_Center)
    {
        pData->rallyPoint = BWAPI::Broodwar->getBuildLocation(BWAPI::UnitTypes::Terran_Bunker, unit->getTilePosition(), 64, false);
        pData->infrastructures.setRallyPoint(BWAPI::Position(pData->rallyPoint));

    }
    else if (unit->getPlayer() == BWAPI::Broodwar->self() && (unit->getType() == BWAPI::UnitTypes::Terran_Barracks || BWAPI::UnitTypes::Terran_Factory || BWAPI::UnitTypes::Terran_Starport))
    {
        unit->setRallyPoint(BWAPI::Position(pData->rallyPoint));
    }
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
    if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
    {
        for (size_t i = 0; i < pData->unitsFarmingMinerals.size(); i++)
        {
            if (pData->unitsFarmingMinerals[i].contains(unit))
            {
                pData->unitsFarmingMinerals[i].erase(unit);
                break;
            }
        }
        for (size_t j = 0; j < pData->unitsFarmingGeysers.size(); j++)
        {
            if (pData->unitsFarmingGeysers[j].contains(unit))
            {
                pData->unitsFarmingGeysers[j].erase(unit);
                break;
            }
        }
    }
}