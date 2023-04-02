#pragma once
#include <unordered_set>
#include <BWAPI.h>

#include <BWEM.h>

#define EARLY_GAME_SCOUT_TIMING 60

#define NWANTED_WORKERS_TOTAL 30
#define NWANTED_WORKERS_FARMING_MINERALS 25

//Definig Game Phase
#define EARLY_GAME 720
#define MID_GAME 1200

#define SUPPLY_PROVIDED_BY_CC 20
#define SUPPLY_PROVIDED_BY_SD 16

//Define army factor for supplies
#define BARRACKS_FACTOR 6
#define FACTORY_FACTOR 8
#define STARPORT_FACTOR 8

#define COUNTER_ATTACK_THRESHOLD 128
#define COUNTER_ATTACK_SUPPLY 120

#define TOTAL_WORKER_LIMIT 160


class Data {
public:
	unsigned int mapWidth;
	unsigned int mapHeight;

	unsigned int maxAggroDistance;

	unsigned int currMinerals;
	unsigned int currGas;
	unsigned int currSupply;

	unsigned int thresholdSupply; 

	unsigned int nWantedBarracksTotal;
	unsigned int nWantedFactoryTotal;
	unsigned int nWantedStarportTotal;

	unsigned int nWantedScienceFacilityTotal;
	unsigned int nWantedEngineeringBayTotal;
	unsigned int nWantedArmoryTotal;

	unsigned int nWantedCommandCenterForTheMoment;

	// counter attack
	// is current in the war time
	bool at_war;
	// if under attack in the last frame
	bool pre_underattack;
	// if under attack in the current frame
	bool now_underattack;
	// count how many frame since not under attack, to decide the counter attack timing
	int not_underattack_counter;

	bool counterAttackFlag = false;

	BWAPI::Unitset scoutUnits;

	BWAPI::Race enemyRace;

	BWAPI::Unitset builders;

	std::vector<BWAPI::Unitset> unitsFarmingMinerals;
	std::vector<BWAPI::Unitset> unitsFarmingGeysers;

	std::vector<unsigned int> nWantedWorkersTotal;
	std::vector<unsigned int> nWantedWorkersFarmingMinerals;
	std::vector<unsigned int> nWantedWorkersFarmingGeysers;

	std::vector<BWAPI::Unit> CommandCenters;
	std::vector<BWAPI::TilePosition> tilePositionCommandCenters;
	std::vector<BWAPI::Position> positionCommandCenters;

	BWAPI::Unitset infrastructures;

	BWAPI::TilePosition rallyPoint;
	BWAPI::TilePosition initialRallyPoint;

	BWAPI::Position enemySpawnLocation;

	std::unordered_set<BWAPI::Unit> availableGeysers;

	std::vector<BWAPI::TilePosition> tilesOfExpansions;
	BWAPI::Unitset blockingMinerals;

	BWAPI::Unitset stuckUnits;
};
