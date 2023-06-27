/* 2021-1574 Eda Grace J. Paragoso
2021-0622 Nancy M. Sayson */

/* EXERCISE #1 output to the answers of Problem #4 and Bonus Question #1 */

#include <iostream>
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

void depthFirstSearch(const vector<Edge>& edges, int startVertex) {
    vector<bool> visited(edges.size() + 1, false);
    stack<int> stack;

    stack.push(startVertex);

    while (!stack.empty()) {
        int currentVertex = stack.top();
        stack.pop();

        if (!visited[currentVertex]) {
            cout << currentVertex << " ";
            visited[currentVertex] = true;
        }

        for (const auto& edge : edges) {
            if (edge.src == currentVertex && !visited[edge.dest]) {
                stack.push(edge.dest);
            } else if (edge.dest == currentVertex && !visited[edge.src]) {
                stack.push(edge.src);
            }
        }
    }
}

int main() {
    // Define the edges and their weights
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
    }
    cout << '\n';

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        cout << i + 1 << " ";
        for (const auto& cost : adjacencyMatrix[i]) {
            cout << setw(3) << cost << " ";
        }
        cout << '\n';
    }
    cout << endl;

    cout << "B. Breadth-First Search Order:\n";
    breadthFirstSearch(edges, 1); // Starting Breadth-First Search from Vertex 1
    cout << "\n\n";

    cout << "C. Depth-First Search Order:\n";
    depthFirstSearch(edges, 1); // Starting Depth-First Search from Vertex 1

    return 0;
}
