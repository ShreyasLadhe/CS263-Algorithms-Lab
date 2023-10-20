#include <iostream>
#include <stack>
using namespace std;

class Vertex;
class Vlist;
class Edge;

class Vertex {
public:
    char data;
    Vlist* con_edges_tail;
    bool visited; // Added to keep track of visited vertices during DFS

    Vertex() {
        con_edges_tail = NULL;
        visited = false;
    }

    Vertex(char data) {
        this->data = data;
        con_edges_tail = NULL;
        visited = false;
    }
};

class Vlist {
public:
    Edge* ptr;
    Vlist* next;

    Vlist() {
        ptr = NULL;
        next = NULL;
    }

    Vlist(Edge* temp1) {
        ptr = temp1;
        next = NULL;
    }
};

class Edge {
public:
    Vertex* end1;
    Vertex* end2;
    bool isDirected;

    Edge() {
        end1 = NULL;
        end2 = NULL;
        isDirected = false;
    }

    Edge(Vertex* v1, Vertex* v2, bool directed) {
        end1 = v1;
        end2 = v2;
        isDirected = directed;
    }
};

int dfs_index = 0;

Vlist* create_LL(Vlist* head1, Edge* e, int i) {
    int edgeno;
    int n;
    cout << "enter number of edges" << endl;
    cin >> n;
    cout << "enter edges connected to node " << i << endl;

    if (head1 == NULL) {
        if (n > 0) {
            Edge* temp = &e[0];
            head1 = new Vlist(temp);
            Vlist* temp2 = head1;
            for (int j = 1; j < n; j++) {
                cout << "enter edges connected to node ";
                cin >> edgeno;
                Edge* temp = &e[edgeno];
                Vlist* newNode = new Vlist(temp);
                temp2->next = newNode;
                temp2 = temp2->next;
            }
        }
    }

    return head1;
}

// Perform DFS and topological sorting
void topologicalSortDFS(Vertex* vertices, int v, stack<int>& s) {
    vertices[v].visited = true;
    Vlist* adj = vertices[v].con_edges_tail;
    
    while (adj != NULL) {
        int index = adj->ptr->end2 - vertices;
        if (!vertices[index].visited) {
            topologicalSortDFS(vertices, index, s);
        }
        adj = adj->next;
    }

    s.push(v);
}

// Perform topological sorting on the entire graph
void topologicalSort(Vertex* vertices, int numVertices) {
    stack<int> s;

    for (int i = 0; i < numVertices; i++) {
        if (!vertices[i].visited) {
            topologicalSortDFS(vertices, i, s);
        }
    }

    cout << "Topological Sorting: ";
    while (!s.empty()) {
        cout << vertices[s.top()].data << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    int numVertices = 5;
    Vertex vertices[numVertices];
    Edge e[7];

    for (int i = 0; i < numVertices; i++) {
        char data;
        cout << "enter vertex data: ";
        cin >> data;
        vertices[i] = Vertex(data);
    }

    for (int i = 0; i < 7; i++) {
        int k1, k2;
        bool directed;
        cout << "enter 1st vertex no., 2nd vertex no., and whether the edge is directed (0 for undirected, 1 for directed) for edge " << i << endl;
        cin >> k1 >> k2 >> directed;
        e[i] = Edge(&vertices[k1], &vertices[k2], directed);
    }

    for (int i = 0; i < numVertices; i++) {
        Vlist* head1 = NULL;
        vertices[i].con_edges_tail = create_LL(head1, e, i);
    }

    topologicalSort(vertices, numVertices);

    return 0;
}
