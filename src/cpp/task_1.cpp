/*
 * Author: Mukhammadkhon Asrorov 
 * Date: 29.12.2023
 * Name: hw-9
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;


struct Vertex {
    int id;    
    int d;     
    int π;     
};


struct Edge {
    int u;   
    int v;   
    int weight;  
};


void initializeSingleSource(vector<Vertex>& graph, int source) {
    for (int i = 0; i < graph.size(); i++) {
        graph[i].d = numeric_limits<int>::max();
        graph[i].π = -1;
    }
    graph[source].d = 0;
}


void relax(vector<Vertex>& graph, Edge& e) {
    int u = e.u;
    int v = e.v;
    int weight = e.weight;
    if (graph[v].d > graph[u].d + weight) {
        graph[v].d = graph[u].d + weight;
        graph[v].π = u;
    }
}


void dijkstra(vector<vector<Edge>>& G, vector<Vertex>& graph, int source) {
    initializeSingleSource(graph, source);
    vector<bool> visited(graph.size(), false);

  
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    Q.push(make_pair(graph[source].d, source));

    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto& edge : G[u]) {
            relax(graph, edge);
            if (!visited[edge.v]) {
                Q.push(std::make_pair(graph[edge.v].d, edge.v));
            }
        }
    }   
}


int main() {
    int numVertices, numEdges, source;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<Vertex> graph(numVertices);
    vector<vector<Edge>> G(numVertices);

    cout << "Enter the edges (u, v, weight):" << endl;
    for (int i = 0; i < numEdges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        Edge e = {u, v, weight};
        G[u].push_back(e);
    }

    cout << "Enter the source vertex: ";
    cin >> source;

    dijkstra(G, graph, source);

    cout << "Shortest distances from source to each vertex:" << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << "Vertex " << i << ": " << graph[i].d << endl;
    }

    return 0;
}
