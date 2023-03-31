#include "SCV_ACTION_BUILD_COMMAND_CENTER.h"
#include "Tools.h"
#include "Data.h"

SCV_ACTION_BUILD_COMMAND_CENTER::SCV_ACTION_BUILD_COMMAND_CENTER(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State SCV_ACTION_BUILD_COMMAND_CENTER::Evaluate(void* data)
{
    return ReturnState(BuildCommandcenter(data));
}

std::string SCV_ACTION_BUILD_COMMAND_CENTER::GetDescription()
{
    return "BUILD COMMAND CENTER";
}


BT_NODE::State SCV_ACTION_BUILD_COMMAND_CENTER::BuildCommandcenter(void* data)
{
    auto instance = BWEM::Map::Instance();
    auto allAreas = instance.Areas();
    std::vector<int> areaWithBases;
    std::vector<int> areaWithMinerals;
    std::vector<double> closestDistances;
    int bestAreaIndex = 0;
    double minDist = BWAPI::Broodwar->mapWidth() * BWAPI::Broodwar->mapWidth() + BWAPI::Broodwar->mapHeight() * BWAPI::Broodwar->mapHeight();;

    for (int a = 0; a < allAreas.size(); a++)
    {
        for (auto base : allAreas[a].Bases())
        {
            areaWithBases.push_back(a);
            break;
        }
        for (auto base : allAreas[a].Minerals())
        {
            areaWithMinerals.push_back(a);
            break;
        }
    }

    for (int aM = 0; aM < areaWithMinerals.size(); aM++)
    {
        double areaDist = BWAPI::Broodwar->mapWidth() * BWAPI::Broodwar->mapWidth() + BWAPI::Broodwar->mapHeight() * BWAPI::Broodwar->mapHeight();
        for (int aB = 0; aB < areaWithBases.size(); aB++)
        {
            double ad = allAreas[areaWithMinerals[aM]].TopLeft().getDistance(allAreas[areaWithMinerals[aB]].TopLeft());
            if (ad < areaDist)
                areaDist = ad;
        }

        if (areaDist > 128)
            closestDistances.push_back(areaDist);
    }

    for (int index = 0; index < closestDistances.size(); index++)
    {
        if (minDist < closestDistances[index])
        {
            minDist = closestDistances[index];
            bestAreaIndex = index;
        }
    }

    auto buildArea = instance.Areas()[areaWithMinerals[bestAreaIndex]];
    buildArea.CreateBases();
}
