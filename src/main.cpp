#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "DAG.h"

using namespace std;

vector<Client> readClients(const string& filename) {
    vector<Client> clients;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return clients;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Client c{};
        ss >> c.start >> c.end >> c.revenue;
        clients.push_back(c);
    }

    return clients;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    string inputFile = argv[1];
    string filename = "data/" + inputFile;

    vector<Client> clients = readClients(filename);

    if (clients.empty()) {
        cerr << "No clients loaded from file: " << filename << endl;
        return 1;
    }

    DAG dag(clients);
    pair<int, vector<int>> result = dag.computeOptimal();

    int maxRevenue = result.first;
    vector<int> path = result.second;

    cout << "There are " << clients.size() << " clients in this file" << endl << endl;
    cout << "Optimal revenue earned is " << maxRevenue << endl;
    cout << "Clients contributing to this optimal revenue: ";

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] + 1;   // convert from 0-based to 1-based
        if (i < path.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;

    string outFile = "out" + inputFile;
    ofstream out(outFile);

    if (!out) {
        cerr << "Could not create output file: " << outFile << endl;
        return 1;
    }

    out << "There are " << clients.size() << " clients in this file" << endl << endl;
    out << "Optimal revenue earned is " << maxRevenue << endl;
    out << "Clients contributing to this optimal revenue: ";

    for (int i = 0; i < path.size(); i++) {
        out << path[i] + 1;   // convert from 0-based to 1-based
        if (i < path.size() - 1) {
            out << ", ";
        }
    }
    out << endl;

    out.close();

    return 0;
}