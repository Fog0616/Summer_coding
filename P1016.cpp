#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Station {
    double distance;
    double price;
};

bool compareStations(Station a, Station b) {
    return a.distance < b.distance;
}

int main() {
    double D1, C, D2, P;
    int N;
    cin >> D1 >> C >> D2 >> P >> N;

    vector<Station> stations(N + 1);
    for (int i = 0; i < N; ++i) {
        cin >> stations[i].distance >> stations[i].price;
    }
    stations[N] = {D1, 0}; // Destination as a station with price 0

    sort(stations.begin(), stations.end(), compareStations);

    if (stations[0].distance != 0) {
        cout << "No Solution" << endl;
        return 0;
    }

    double maxDistancePerTank = C * D2;
    double currentTank = 0;
    double totalCost = 0;
    double currentDistance = 0;

    for (int i = 0; i <= N;) {
        if (i > 0 && stations[i].distance > currentDistance + maxDistancePerTank) {
            cout << "No Solution" << endl;
            return 0;
        }

        int nextStation = -1;
        double minPrice = 1e9;

        for (int j = i + 1; j <= N && stations[j].distance <= currentDistance + maxDistancePerTank; ++j) {
            if (stations[j].price < minPrice) {
                minPrice = stations[j].price;
                nextStation = j;
            }
            if (stations[j].price < stations[i].price) break;
        }

        if (nextStation == -1 || nextStation == i) {
            cout << "No Solution" << endl;
            return 0;
        }

        double distanceToNext = stations[nextStation].distance - currentDistance;
        double neededFuel = distanceToNext / D2;
        
        if (neededFuel > currentTank) {
            totalCost += (neededFuel - currentTank) * stations[i].price;
            currentTank = neededFuel;
        }

        currentTank -= neededFuel;
        currentDistance = stations[nextStation].distance;
        i = nextStation;
    }

    cout << fixed << setprecision(2) << totalCost << endl;
    return 0;
}