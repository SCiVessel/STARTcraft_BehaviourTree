#pragma once
#include <unordered_set>
#include <BWAPI.h>

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 6

#define NWANTED_WORKERS_TOTAL 30
#define NWANTED_WORKERS_FARMING_MINERALS 25

//Definig Game Phase
#define EARLY_GAME 360
#define MID_GAME 900

#define SUPPLY_PROVIDED_BY_CC 20
#define SUPPLY_PROVIDED_BY_SD 16


class Data {
public:
	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply; 

	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMinerals;

	int nWantedBarracksTotal;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;
	std::unordered_set<BWAPI::Unit> unitsFarmingGeysers;
};
