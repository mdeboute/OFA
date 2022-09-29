#include "parser.hpp"
#include "filesystem.hpp"
#include "mip_formulation.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    const string root_dir = fs::current_path().parent_path();
    const string data_dir = root_dir + "/data";
    // const string data_dir = "../data";

    string map_file = data_dir + "/map.ppm";
    string config_file = data_dir + "/config.txt";

    vector<float> config = parseConfig(config_file);
    vector<vector<int>> map = parseMap(map_file);

    cout << "Number of angles: " << config[0] << endl;
    cout << "Furnace radius: " << config[1] << endl;
    cout << "Radius of action of a firefighter: " << config[2] << endl;
    cout << endl;
    cout << "Map size: " << map.size() << "x" << map[0].size() << endl;

    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == BLUE)
                cout << "~";
            if (map[y][x] == YELLOW)
                cout << ".";
            if (map[y][x] == BLACK)
                cout << "$";
            if (map[y][x] == RED)
                cout << "X";
            if (map[y][x] == GREEN)
                cout << "O";
        }
        cout << endl;
    }

    // map = solve(map, config);

    return 0;
}