#pragma once
#include <unordered_set>
#include <BWAPI.h>

// #define THRESHOLD1_MINERALS 200
#define EARLY_GAME_SUPPLY_THRESHOLD 10

#define NWANTED_WORKERS_TOTAL 30
#define NWANTED_WORKERS_FARMING_MINERALS 25

//Definig Game Phase
#define EARLY_GAME 360
#define MID_GAME 900

#define SUPPLY_PROVIDED_BY_CC 20
#define SUPPLY_PROVIDED_BY_SD 16

//Define army factor for supplies
#define BARRACKS_FACTOR 6
#define FACTORY_FACTOR 8
#define STARPORT_FACTOR 8

#define RETALIATE_DISTANCE 1024


class Data {
public:
	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply; 

	int nWantedBarracksTotal;
	int nWantedFactoryTotal;
	int nWantedStarportTotal;

	std::vector<std::unordered_set<BWAPI::Unit>> unitsFarmingMinerals;
	std::vector<std::unordered_set<BWAPI::Unit>> unitsFarmingGeysers;

	std::vector<int> nWantedWorkersTotal;
	std::vector<int> nWantedWorkersFarmingMinerals;
	std::vector<int> nWantedWorkersFarmingGeysers;

	std::vector<BWAPI::Unit> CommandCenters;
	std::vector<BWAPI::TilePosition> tilePositionCommandCenters;
	std::vector<BWAPI::Position> positionCommandCenters;

	// int nWantedWorkersTotal;
	// int nWantedWorkersFarmingMinerals;
	// int nWantedWorkersFarmingGeysers;

	// std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	// std::unordered_set<BWAPI::Unit> unitsFarmingGeysers;

	std::unordered_set<BWAPI::Unit> availableGeysers;
};
