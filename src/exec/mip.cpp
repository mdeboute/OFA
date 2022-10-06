#include "file_io.hpp"
#include "mip_formulation.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./mip.out <input_dir>" << endl;
        return 1;
    }

    const string data_dir = argv[1];
    const string map_file = data_dir + "/map.ppm";
    const string config_file = data_dir + "/config.txt";

    vector<float> config = parseConfig(config_file);
    vector<vector<Color>> map = parseMap(map_file);

    cout << "Number of angles: " << config[0] << endl;
    cout << "Furnace radius: " << config[1] << endl;
    cout << "Radius of action of a firefighter: " << config[2] << endl;
    cout << endl;
    cout << "Map size: " << map.size() << "x" << map[0].size() << endl;

    display_map(map);

    map = solve(map, config);

    const string result_dir = "../solutions";
    const string result_map_file = result_dir + "/result.ppm";
    cout << "Writing result to " << result_map_file << endl;
    writeMap(result_map_file, map);

    display_map(map);

    return 0;
}