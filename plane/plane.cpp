#include "plane.h"
#include <iostream>

using namespace std;

void Airport::createPlane(const string& plane, const vector<string>& towns) {
    if (plane_stop.count(plane)) {
        cout << "Plane " << plane << " already exists." << endl;
        return;
    }

    plane_stop[plane] = towns;

    for (const auto& town : towns) {
        town_planes[town].insert(plane);
    }

    cout << "Plane " << plane << " created (" << towns.size() << " stops)" << endl;
}

void Airport::planesForTown(const string& town) const {
    auto it = town_planes.find(town);
    if (it == town_planes.end()) {
        cout << "There are no planes flying through the town " << town << "." << endl;
        return;
    }

    cout << "planes that are in the town" << town << ":" << endl;
    for (const auto& plane : it->second) {
        cout << "- " << plane << endl;
    }
}

void Airport::townsForPlane(const string& plane) const {
    auto it = plane_stop.find(plane);
    if (it == plane_stop.end()) {
        cout << "Plane " << plane << " not found." << endl;
        return;
    }

    cout << "Plane " << plane << " stops: " << endl;
    for (const auto& town : it->second) {
        cout << "- " << town;

        auto town_it = town_planes.find(town);
        if (town_it != town_planes.end() && town_it->second.size() > 1) {
            cout << " (stops are also made: ";
            for (const auto& other_plane : town_it->second) {
                if (other_plane != plane) {
                    cout << other_plane << " ";
                }
            }
            cout << ")";
        }
        cout << endl;
    }
}

void Airport::all() const {
    if (plane_stop.empty()) {
        cout << "No planes registered." << endl;
        return;
    }

    cout << "All registered planes:" << endl;
    for (const auto& [plane, towns] : plane_stop) {
        cout << "- " << plane << " (stops: ";
        for (size_t i = 0; i < towns.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << towns[i];
        }
        cout << ")" << endl;
    }
}
