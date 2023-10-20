#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Vertex;
class Vlist;
class Edge;

class Vertex {
public:
    char data;
    Vlist* con_edges_tail;

    Vertex() {
        con_edges_tail = NULL;
    }

    Vertex(char data) {
        this->data = data;
        this->con_edges_tail = NULL;
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
    bool isDirected; // New attribute to represent if the edge is directed

    Edge() {
        end1 = NULL;
        end2 = NULL;
        isDirected = false; // Default to undirected
    }

    Edge(Vertex* v1, Vertex* v2, bool directed) {
        this->end1 = v1;
        this->end2 = v2;
        this->isDirected = directed;
    }
};

Vlist* create_LL(Vlist* head1, Edge* e, int i) {
    int edgeno;

    int n; // no. of edges
    cout << "enter number of edges" << endl;
    cin >> n;
    cout << "enter edges connected to node " << i << endl;
    cin >> edgeno;
    if (head1 == NULL) {
        if (edgeno >= 0 && edgeno < 7) {
            Edge* temp = &e[edgeno];
            head1 = new Vlist(temp);
        } else {
            cout << "Invalid edge number" << endl;
            return NULL;
        }
    }

    n = n - 1;
    Vlist* temp2 = head1;
    while (n != 0) {
        cout << "enter edges connected to node ";
        cin >> edgeno;
        Edge* temp = &e[edgeno];
        Vlist* newNode = new Vlist(temp);
        temp2->next = newNode;
        n--;

        temp2 = temp2->next; // added at the end and it worked
    }
    return head1;
}

// BFS Algorithm
void BFS(Vertex* vertices, int start, int numVertices) {
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    cout << "BFS starting from vertex " << vertices[start].data << ": ";

    queue<int> q;
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int currentVertex = q.front();
        cout << vertices[currentVertex].data << " ";
        q.pop();

        Vlist* adj = vertices[currentVertex].con_edges_tail;
        while (adj != NULL) {
            int index = adj->ptr->isDirected ? adj->ptr->end2 - vertices : adj->ptr->end1 - vertices;
            if (!visited[index]) {
                visited[index] = true;
                q.push(index);
            }
            adj = adj->next;
        }
    }

    cout << endl;
    delete[] visited;
}

// DFS Algorithm
void DFS(Vertex* vertices, int start, int numVertices) {
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    cout << "DFS starting from vertex " << vertices[start].data << ": ";

    stack<int> s;
    visited[start] = true;
    s.push(start);
    
    while (!s.empty()) {
        int currentVertex = s.top();
        cout << vertices[currentVertex].data << " ";
        s.pop();

        Vlist* adj = vertices[currentVertex].con_edges_tail;
        while (adj != NULL) {
            int index = adj->ptr->isDirected ? adj->ptr->end2 - vertices : adj->ptr->end1 - vertices;
            if (!visited[index]) {
                visited[index] = true;
                s.push(index);
            }
            adj = adj->next;
        }
    }

    cout << endl;
    delete[] visited;
}

int main() {
    int numVertices = 5;
    Vertex vertices[numVertices];
    Edge e[7];

    // vertices data
    for (int i = 0; i < numVertices; i++) {
        char data;
        cout << "enter vertex data: ";
        cin >> data;
        vertices[i] = Vertex(data);
    }

    // edges end1 and end2, and whether they are directed
    for (int i = 0; i < 7; i++) {
        int k1, k2;
        bool directed;
        cout << "enter 1st vertex no., 2nd vertex no., and whether the edge is directed (0 for undirected, 1 for directed) for edge " << i << endl;
        cin >> k1 >> k2 >> directed;
        e[i] = Edge(&vertices[k1], &vertices[k2], directed);
    }

    for (int i = 0; i < numVertices; i++) {
        Vlist* head1 = NULL;
        // head returned from LL of type Vlist
        vertices[i].con_edges_tail = create_LL(head1, e, i);
    }

    // display
    for (int i = 0; i < numVertices; i++) {
        cout << "for vertex " << vertices[i].data << endl;
        Vlist* ptr2 = vertices[i].con_edges_tail;
        while (ptr2 != NULL) {
            if (ptr2->ptr->isDirected) {
                cout << "directed edge (" << ptr2->ptr->end1->data << " -> " << ptr2->ptr->end2->data << ")" << endl;
            } else {
                cout << "undirected edge (" << ptr2->ptr->end1->data << " - " << ptr2->ptr->end2->data << ")" << endl;
            }
            ptr2 = ptr2->next;
        }
    }

    int choice;
    cout << "Select algorithm (1 for BFS, 2 for DFS): ";
    cin >> choice;

    int startVertex;
    cout << "Enter the starting vertex (0 to " << numVertices - 1 << "): ";
    cin >> startVertex;

    switch (choice) {
        case 1:
            BFS(vertices, startVertex, numVertices);
            break;
        case 2:
            DFS(vertices, startVertex, numVertices);
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
