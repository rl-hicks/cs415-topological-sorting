//
// Created by levi on 3/29/2026.
//


#ifndef DAG_H
#define DAG_H

#include <vector>
#include <iostream>
using namespace std;


struct Client {
    int start;
    int end;
    int revenue;
};

class DAG {
public:
    vector<Client> clients;
    vector<vector<int>> graph;
    int START, END;

    DAG(const vector<Client>& c);

    void buildGraph();
    void printGraph();
    vector<int> topologicalSort();
    pair<int, vector<int>> computeOptimal();

};

#endif