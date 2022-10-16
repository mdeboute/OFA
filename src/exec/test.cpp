#include "Graph/FighterVertex.hpp"
#include "Graph/FireVertex.hpp"
#include "utils.hpp"
#include "brute_force.hpp"

#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: ./test.out <input_dir>" << endl;
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

    // display_map(map);

    Graph graph = calculate_graph_data(map, config);

    vector<FireVertex> fireVertices = graph.getFireVertexTab();
    vector<FighterVertex> fighterVertices = graph.getFigtherVertexTab();

    cout << "Number of fires: " << fireVertices.size() << endl;
    cout << "Number of  potential fighters: " << fighterVertices.size() << endl;

    // TODO: compute a lower bound on the number of fighters needed to extinguish all fires

    vector<vector<FighterVertex>> partitions = findPartitions(fighterVertices, fireVertices.size(), 4);

    cout << "Number of partitions: " << partitions.size() << endl;

    const vector<FighterVertex> bestTeam = solve(partitions, fireVertices);

    for (FighterVertex fighter : bestTeam)
    {
        Position pos = fighter.getPos();
        map[pos.getY()][pos.getX()] = GREEN;
    }

    cout << "Best team: \n"
         << endl;
    for (FighterVertex fighter : bestTeam)
    {
        cout << fighter << endl;
    }

    vector<string> splittedString = splitString(data_dir, "/");
    const string result_file = "../solution/result_" + splittedString[1] + ".ppm";
    cout << "Writing result to " << result_file << endl;

    writeMap(result_file, map);

    // display_map(map);

    return 0;
}