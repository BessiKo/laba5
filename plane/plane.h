#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Airport {
private:
    unordered_map<string, vector<string>> plane_stop;
    unordered_map<string, unordered_set<string>> town_planes;

public:
    void createPlane(const string& plane, const vector<string>& towns);
    void planesForTown(const string& town) const;
    void townsForPlane(const string& plane) const;
    void all() const;
};

#endif
