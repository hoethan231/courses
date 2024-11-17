#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Compare {
    bool operator()(Edge a, Edge b) {
        return a.weight > b.weight;
    }
};

vector<int> primMST(int V, vector<vector<Edge>>& graph) {
    vector<int> parent(V, -1);
    vector<int> key(V, numeric_limits<int>::max());
    vector<bool> mst(V, false);

    priority_queue<Edge, vector<Edge>, Compare> pq;

    key[0] = 0;
    pq.push({0, -1, 0});

    while (!pq.empty()) {
        Edge front = pq.top();
        pq.pop();

        int u = front.src;
        int v = front.dest;

        if (mst[v]) continue;

        mst[u] = true;
        mst[v] = true;

        parent[v] = u;

        for (Edge& edge : graph[v]) {
            if (!mst[edge.dest] && edge.weight < key[edge.dest]) {
                key[edge.dest] = edge.weight;
                pq.push({edge.dest, edge.src, edge.weight});
            }
        }
    }

    vector<int> result;
    for (int i = 1; i < V; i++) {
        result.push_back(parent[i]);
    }

    return result;
}

vector<Edge> kruskalMST(int V, vector<vector<Edge>>& graph) {
    vector<int> parent(V, -1);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    vector<Edge> edges;
    for (int i = 0; i < V; i++) {
        for (Edge& edge : graph[i]) {
            edges.push_back(edge);
        }
    }

    sort(edges.begin(), edges.end(), Compare());

    vector<Edge> result;
    for (Edge& edge : edges) {
        int src = edge.src;
        int dest = edge.dest;

        if (findParent(parent, src) != findParent(parent, dest)) {
            result.push_back(edge);
            unionSets(parent, rank, src, dest);
        }
    }

    return result;
}

int findParent(vector<int>& parent, int node) {
    if (parent[node] == -1) {
        return node;
    }
    return findParent(parent, parent[node]);
}

void unionSets(vector<int>& parent, vector<int>& rank, int src, int dest) {
    int srcParent = findParent(parent, src);
    int destParent = findParent(parent, dest);

    if (rank[srcParent] < rank[destParent]) {
        parent[srcParent] = destParent;
    } else if (rank[srcParent] > rank[destParent]) {
        parent[destParent] = srcParent;
    } else {
        parent[destParent] = srcParent;
        rank[srcParent]++;
    }
}

int main() {
    int V = 5;
    vector<vector<Edge>> graph(V);

    graph[0].push_back({0, 1, 2});
    graph[0].push_back({0, 3, 6});
    graph[1].push_back({1, 2, 3});
    graph[1].push_back({1, 3, 8});
    graph[2].push_back({2, 3, 5});
    graph[3].push_back({3, 4, 7});

    vector<int> result = primMST(V, graph);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (int i = 1; i < V; i++) {
        cout << result[i] << " - " << i << endl;
    }

    return 0;
}