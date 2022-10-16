#include "brute_force.hpp"
#include <vector>
#include "Graph/FighterVertex.hpp"
#include <cmath>

std::vector<std::vector<FighterVertex>> findPartitions(std::vector<FighterVertex> fighters, int upperBound, int lowerBound)
{
    int n = fighters.size();
    std::vector<std::vector<FighterVertex>> partitions;

    for (int i = 0; i < std::pow(2, n); i++)
    {
        std::vector<FighterVertex> subset;

        // we want the subset of size at most upperBound and at least lowerBound
        if (std::bitset<32>(i).count() <= upperBound && std::bitset<32>(i).count() >= lowerBound)
        {
            for (int j = 0; j < n; j++)
            {
                if (i & (1 << j))
                {
                    subset.push_back(fighters[j]);
                }
            }
            partitions.push_back(subset);
        }
    }
    return partitions;
}

bool checker(std::vector<FighterVertex> fighters, std::vector<FireVertex> fires)
{
    for (FireVertex fire : fires)
    {
        bool find = false;
        for (FighterVertex fighter : fighters)
        {
            if (fighter.stopFire(fire))
            {
                find = true;
                break;
            }
        }
        if (!find)
        {
            return false;
        }
    }
    return true;
}

std::vector<FighterVertex> solve(std::vector<std::vector<FighterVertex>> partitions, std::vector<FireVertex> fires)
{
    std::vector<FighterVertex> bestTeam;
    int bestSize = fires.size();
    for (std::vector<FighterVertex> team : partitions)
    {
        if (checker(team, fires) == true && team.size() <= bestSize)
        {
            bestTeam = team;
        }
    }
    return bestTeam;
}
