#include "plane.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Command {
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    EXIT,
    UNKNOWN
};

Command comm(const string& input) {
    string cmd = input;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

    if (cmd == "CREATE_PLANE") return Command::CREATE_PLANE;
    if (cmd == "PLANES_FOR_TOWN") return Command::PLANES_FOR_TOWN;
    if (cmd == "TOWNS_FOR_PLANE") return Command::TOWNS_FOR_PLANE;
    if (cmd == "PLANES") return Command::PLANES;
    if (cmd == "EXIT") return Command::EXIT;
    return Command::UNKNOWN;
}

vector<string> split(const string& s) {
    vector<string> result;
    istringstream iss(s);
    string token;

    while (iss >> token) {
        result.push_back(token);
    }

    return result;
}

int main() {
    Airport system;
    string line;

    while (true) {
        getline(cin, line);
        if (line.empty()) continue;

        auto tokens = split(line);
        if (tokens.empty()) continue;

        Command cmd = comm(tokens[0]);

        switch (cmd) {
            case Command::CREATE_PLANE:
                if (tokens.size() >= 3) {
                    string plane = tokens[1];
                    vector<string> towns(tokens.begin() + 2, tokens.end());
                    system.createPlane(plane, towns);
                } else {
                    cout << "Incorrect parameters" << endl;
                }
                break;

            case Command::PLANES_FOR_TOWN:
                if (tokens.size() == 2) {
                    system.planesForTown(tokens[1]);
                } else {
                    cout << "Incorrect parameters" << endl;
                }
                break;

            case Command::TOWNS_FOR_PLANE:
                if (tokens.size() == 2) {
                    system.townsForPlane(tokens[1]);
                } else {
                    cout << "Incorrect parameters" << endl;
                }
                break;

            case Command::PLANES:
                system.all();
                break;

            case Command::EXIT:
                return 0;

            case Command::UNKNOWN:
            default:
                cout << "Incorrect command" << endl;
                break;
        }
    }

    return 0;
}
