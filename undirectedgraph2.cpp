/* 2021-1574 Eda Grace J. Paragoso
2021-0622 Nancy M. Sayson */

/* EXERCISE #1 output to the answers of Problem #4 and Bonus Question #1 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    int src;
    int dest;
    int weight;
};

void breadthFirstSearch(const vector<Edge>& edges, int startVertex) {
    vector<bool> visited(edges.size() + 1, false);
    queue<int> queue;

    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        cout << currentVertex << " ";

        for (const auto& edge : edges) {
            if (edge.src == currentVertex && !visited[edge.dest]) {
                visited[edge.dest] = true;
                queue.push(edge.dest);
            } else if (edge.dest == currentVertex && !visited[edge.src]) {
                visited[edge.src] = true;
                queue.push(edge.src);
            }
        }
    }
}

void depthFirstSearch(const vector<Edge>& edges, vector<bool>& visited, int currentVertex) {
    visited[currentVertex] = true;
    cout << currentVertex << " ";

    for (const auto& edge : edges) {
        if (edge.src == currentVertex && !visited[edge.dest]) {
            depthFirstSearch(edges, visited, edge.dest);
        } else if (edge.dest == currentVertex && !visited[edge.src]) {
            depthFirstSearch(edges, visited, edge.src);
        }
    }
}

bool compareEdges(const Edge& edge1, const Edge& edge2) {
    return edge1.weight < edge2.weight;
}

int find(vector<int>& parent, int vertex) {
    if (parent[vertex] == -1)
        return vertex;
    return find(parent, parent[vertex]);
}

void unionSets(vector<int>& parent, int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);
    parent[xRoot] = yRoot;
}

void constructMinimumSpanningTree(vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdges);

    int numVertices = edges.size();
    vector<int> parent(numVertices, -1);
    vector<Edge> selectedEdges;

    cout << "Progress of Minimum Spanning Tree Construction:\n";

    for (const auto& edge : edges) {
        int srcRoot = find(parent, edge.src);
        int destRoot = find(parent, edge.dest);

        if (srcRoot != destRoot) {
            selectedEdges.push_back(edge);
            unionSets(parent, srcRoot, destRoot);
            cout << "Added edge: (" << edge.src << ", " << edge.dest << ", " << edge.weight << ")\n";
        }
    }

    cout << "\nMinimum Cost Spanning Tree Edges:\n";
    for (const auto& edge : selectedEdges) {
        cout << "(" << edge.src << ", " << edge.dest << ", " << edge.weight << ")\n";
    }
}

int main() {
/* UNDIRECTED GRAPH */
    cout << "Undirected Graph:\n";
    vector<Edge> edges = {
        {3, 7, 1}, {1, 2, 2}, {3, 4, 3}, {4, 7, 5}, {2, 6, 6},
        {1, 6, 8}, {2, 3, 10}, {6, 7, 11}, {3, 6, 12}, {7, 8, 15},
        {4, 8, 20}, {1, 5, 22}, {5, 6, 25}
    };

    // Print the connections per edge with their weights
    for (const auto& edge : edges) {
        cout << "Vertex " << edge.src << " is connected to Vertex " << edge.dest
                  << " with weight of " << edge.weight << endl;
    }
    cout << endl;

/* COST-ADJACENCY MATRIX */
    cout << "A. Cost-Adjacency-Matrix:\n";
    vector<vector<int>> adjacencyMatrix = {
        {0, 2, 0, 0, 22, 8, 0, 0},
        {2, 0, 10, 0, 0, 6, 0, 0},
        {0, 10, 0, 3, 0, 12, 1, 0},
        {0, 0, 3, 0, 0, 0, 5, 20},
        {22, 0, 0, 0, 0, 25, 0, 0},
        {8, 6, 12, 0, 25, 0, 11, 0},
        {0, 0, 1, 5, 0, 11, 0, 5},
        {0, 0, 0, 20, 0, 0, 5, 0}
    };

    cout << "  ";
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        cout << setw(3) << i + 1 << " ";
    } cout << '\n';

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        cout << i + 1 << " ";
        for (const auto& cost : adjacencyMatrix[i]) {
            cout << setw(3) << cost << " ";
        }
        cout << '\n';
    } cout << endl;

/* BREADTH-FIRST SEARCH */
    cout << "B. Breadth-First Search Order:\n";
    breadthFirstSearch(edges, 1); // Starting Breadth-First Search from Vertex 1
    cout << "\n\n";

/* DEPTH-FIRST SEARCH */
    cout << "C. Depth-First Search Order:\n";
    int numVertices = 8;
    vector<bool> visited(numVertices + 1, false);

    for (int vertex = 1; vertex <= numVertices; ++vertex) {
        if (!visited[vertex]) {
            depthFirstSearch(edges, visited, vertex);
        }
    }

/* MINIMUM COST SPANNING TREE USING KRUSKAL'S ALGORITHM */
    cout << "Bonus Question - Minimum Cost Spanning Tree using Kruskal's Algorithm:\n";
    for (const auto& edge : edges) {
        cout << "Vertex " << edge.src << " is connected to Vertex " << edge.dest
             << " with weight of " << edge.weight << endl;
    } cout << endl;
    constructMinimumSpanningTree(edges);

    return 0;
}
