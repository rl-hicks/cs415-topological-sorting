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
        cerr << "Error in Function: readClient()... opening file: " << filename << endl;
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

    string filename = "data/" + string(argv[1]);

    cout << "Filename: " << filename << endl;



    vector<Client> clients = readClients(filename);

    for (Client& c : clients) {
        cout << c.end << endl << c.revenue << endl << c.start << endl << endl;
    }

    DAG dag(clients);

    cout << "\nGraph:\n";
    dag.printGraph();

    vector<int> topo = dag.topologicalSort();

    cout << "\nTopological Order:\n";
    for (int v : topo) {
        cout << v << " ";
    }
    cout << endl;

    cout << "START = " << dag.START << ", END = " << dag.END << endl;


    auto result = dag.computeOptimal();

    int maxRevenue = result.first;
    vector<int> path = result.second;

    cout << "\nMax Revenue: " << maxRevenue << endl;

    cout << "Selected Clients:\n";
    for (int idx : path) {
        cout << idx << ": "
             << dag.clients[idx].start << ", "
             << dag.clients[idx].end << ", "
             << dag.clients[idx].revenue << endl;
    }



}