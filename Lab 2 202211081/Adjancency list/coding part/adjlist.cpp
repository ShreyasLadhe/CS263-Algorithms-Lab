#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Graph {
private:
    int V;          
    Node** adjList; 

public:
    Graph(int vertices);
    ~Graph();
    void addEdge(int u, int v);
    void printGraph();
};

Graph::Graph(int vertices) {
    V = vertices;
    adjList = new Node*[V];
    for (int i = 0; i < V; ++i) {
        adjList[i] = nullptr;
    }
}

Graph::~Graph() {
    for (int i = 0; i < V; ++i) {
        Node* current = adjList[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
}

void Graph::addEdge(int u, int v) {
    Node* newNode = new Node(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = new Node(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

void Graph::printGraph() {
    for (int i = 0; i < V; ++i) {
        cout << "Adjacency list for vertex " << i << ": ";
        Node* current = adjList[i];
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
}

int main() {
    Graph graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.printGraph();

    return 0;
}
