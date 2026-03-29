//
// Created by levi on 3/29/2026.
//

#include "DAG.h"
#include <queue>

#include "DAG.h"

DAG::DAG(const vector<Client>& c) {
    clients = c;
    buildGraph();
}

void DAG::buildGraph() {
    int n = clients.size();
    START = n;
    END = n + 1;

    graph.resize(n + 2);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && clients[i].end <= clients[j].start) {
                graph[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        bool hasIncoming = false;
        for (int j = 0; j < n; j++) {
            if (j != i && clients[j].end <= clients[i].start) {
                hasIncoming = true;
                break;
            }
        }
        if (!hasIncoming) {
            graph[START].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (graph[i].empty()) {
            graph[i].push_back(END);
        }
    }
}

void DAG::printGraph() {
    for (int i = 0; i < graph.size(); i++) {
        cout << i << ": ";
        for (int v : graph[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

vector<int> DAG::topologicalSort() {
    int V = graph.size();
    vector<int> indegree(V, 0);

    for (int u = 0; u < V; u++) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return order;
}

pair<int, vector<int>> DAG::computeOptimal() {
    vector<int> topo = topologicalSort();
    int V = graph.size();

    vector<int> F(V, 0);
    vector<int> next(V, -1);

    // process in reverse topo order
    for (int i = V - 1; i >= 0; i--) {
        int u = topo[i];

        if (u == END) {
            F[u] = 0;
            continue;
        }

        int weight = (u == START) ? 0 : clients[u].revenue;

        int best = -1;
        int bestNeighbor = -1;

        for (int v : graph[u]) {
            if (F[v] > best) {
                best = F[v];
                bestNeighbor = v;
            }
        }

        if (best != -1) {
            F[u] = weight + best;
            next[u] = bestNeighbor;
        } else {
            F[u] = weight;
        }
    }

    // reconstruct path
    vector<int> path;
    int cur = next[START];

    while (cur != -1 && cur != END) {
        path.push_back(cur);
        cur = next[cur];
    }

    return {F[START], path};
}