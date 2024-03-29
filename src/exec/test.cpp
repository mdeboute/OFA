#include "Graph/FighterVertex.hpp"
#include "Graph/FireVertex.hpp"
#include "utils.hpp"
#include "file_io.hpp"
#include "brute_force.hpp"
#include "greedy.hpp"
#include "simulated_annealing.hpp"

#include <vector>
#include <cstring>

using namespace std;

const string MAP_FILE = "/map.ppm";
const string CONFIG_FILE = "/config.txt";

void display_usage()
{
    cout << "Usage: ./test <instance_directory> <algorithm>" << endl;
    cout << "Where <algorithm> is one of:" << endl;
    cout << "-b or --bruteforce" << endl;
    cout << "-g or --greedy" << endl;
    cout << "-sa or --simulated_annealing" << endl;
}

void display_solution(const vector<FighterVertex> solution)
{
    for (FighterVertex fighter : solution)
    {
        cout << "We place a fighter at position (" << fighter.getPos().getX() << ", " << fighter.getPos().getY() << ")" << endl;
    }
}

void display_data(vector<float> config, vector<vector<Color>> map)
{
    cout << "Number of angles: " << config[0] << endl;
    cout << "Furnace radius: " << config[1] << endl;
    cout << "Radius of action of a firefighter: " << config[2] << endl;
    cout << "Map size: " << map.size() << "x" << map[0].size() << endl;
    cout << endl;
}

const string get_result_file(const string data_dir)
{
    vector<string> splitString = split_string(data_dir, "/");
    if (splitString[splitString.size() - 1].empty())
        splitString.erase(splitString.end() - 1);
    const string result_file = "solution/result_" + splitString[splitString.size() - 1] + ".ppm";
    cout << "\nWriting result to " << result_file << endl;
    return result_file;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        display_usage();
        return 1;
    }

    int time_limit = 600;

    if (argc == 4)
    {
        time_limit = atoi(argv[3]);
    }

    const string data_dir = argv[1];
    const string map_file = data_dir + MAP_FILE;
    const string config_file = data_dir + CONFIG_FILE;

    if (strcmp(argv[2], "-b") == 0 || strcmp(argv[2], "--bruteforce") == 0)
    {
        vector<float> config = parse_config(config_file);
        vector<vector<Color>> map = parse_map(map_file);
        display_data(config, map);
        cout << "Necessary number of angles: " << get_nb_angles(map) << endl;
        cout << endl;
        Graph graph = calculate_graph_data(map, config, true, true, true);
        vector<FighterVertex> bestTeam = better_bruteforce_solve(graph);
        display_solution(bestTeam);
        const string result_file = get_result_file(data_dir);
        write_solution(result_file, map, config, bestTeam);
    }
    else if (strcmp(argv[2], "-g") == 0 || strcmp(argv[2], "--greedy") == 0)
    {
        vector<float> config = parse_config(config_file);
        vector<vector<Color>> map = parse_map(map_file);
        display_data(config, map);
        cout << "Necessary number of angles: " << get_nb_angles(map) << endl;
        cout << endl;
        Graph graph = calculate_graph_data(map, config, true, true, true);
        vector<FighterVertex> bestTeam = greedy_solve(graph, true);
        display_solution(bestTeam);
        const string result_file = get_result_file(data_dir);
        write_solution(result_file, map, config, bestTeam);
    }
    else if (strcmp(argv[2], "-sa") == 0 || strcmp(argv[2], "--simulated_annealing") == 0)
    {
        vector<float> config = parse_config(config_file);
        vector<vector<Color>> map = parse_map(map_file);
        display_data(config, map);
        cout << "Necessary number of angles: " << get_nb_angles(map) << endl;
        cout << endl;
        Graph graph = calculate_graph_data(map, config, true, true, true);
        int nb_iterations = graph.getFigtherVertexList().size() * 10;
        float initial_temperature = get_initial_temperature(graph, 0.8, 100, 1000);
        cout << "Initial temperature: " << initial_temperature << endl;
        float final_temperature = 0.01;
        float coolingRate = 0.1;
        vector<FighterVertex> bestTeam = sa_solve(graph, nb_iterations, initial_temperature, final_temperature, coolingRate);
        display_solution(bestTeam);
        const string result_file = get_result_file(data_dir);
        write_solution(result_file, map, config, bestTeam);
    }
    else
    {
        display_usage();
        return 1;
    }
    return 0;
}
