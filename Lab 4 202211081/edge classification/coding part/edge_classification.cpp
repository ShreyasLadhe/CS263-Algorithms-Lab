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

    Vertex() {
        con_edges_tail = nullptr;
    }

    Vertex(char data) {
        this->data = data;
        this->con_edges_tail = nullptr;
    }
};

class Vlist {
public:
    Edge* ptr;
    Vlist* next;

    Vlist() {
        ptr = nullptr;
        next = nullptr;
    }

    Vlist(Edge* temp1) {
        ptr = temp1;
        next = nullptr;
    }
};

class Edge {
public:
    Vertex* end1;
    Vertex* end2;
    int edgeType;

    Edge() {
        end1 = nullptr;
        end2 = nullptr;
        edgeType = -1; 
    }

    Edge(Vertex* v1, Vertex* v2, int type) {
        this->end1 = v1;
        this->end2 = v2;
        this->edgeType = type;
    }
};

Vlist* create_LL(Vlist* head1, Edge* e, int i) {
    int edgeno;

    int n; 
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

        temp2 = temp2->next; 
    }
    return head1;
}

Vertex vertices[5]; 

void classifyEdges(Vertex* v, int parent, int& time, Edge e[], int edgeType[]) {
    for (Vlist* ptr2 = v->con_edges_tail; ptr2 != nullptr; ptr2 = ptr2->next) {
        Edge* edge = ptr2->ptr;

        if (edgeType[edge - e] == -1) {
            edgeType[edge - e] = 0; // Tree edge

            if (edge->end2 == v)
                swap(edge->end1, edge->end2);

            classifyEdges(edge->end2, v - vertices, time, e, edgeType);
        } else if (edgeType[edge - e] == 0) {
            edgeType[edge - e] = 1; // Back edge
        } else {
            if (parent == edge->end2 - vertices) {
                edgeType[edge - e] = 2; // Forward edge
            } else {
                edgeType[edge - e] = 3; // Cross edge
            }
        }
    }
}

int main() {
    int numVertices = 5;
    Edge e[7];
    int edgeType[7];

    for (int i = 0; i < numVertices; i++) {
        char data;
        cout << "enter vertex data: ";
        cin >> data;
        vertices[i] = Vertex(data);
    }

    for (int i = 0; i < 7; i++) {
        int k1, k2;
        cout << "enter 1st vertex no. and 2nd vertex no. for edge " << i << endl;
        cin >> k1 >> k2;
        e[i] = Edge(&vertices[k1], &vertices[k2], -1);
    }

    for (int i = 0; i < numVertices; i++) {
        Vlist* head1 = nullptr;
        vertices[i].con_edges_tail = create_LL(head1, e, i);
    }

    int startVertex, time;
    cout << "Enter the starting vertex (0 to " << numVertices - 1 << "): ";
    cin >> startVertex;

    classifyEdges(&vertices[startVertex], -1, time, e, edgeType);

    for (int i = 0; i < 7; i++) {
        cout << "Edge " << i << " is a ";
        switch (edgeType[i]) {
            case 0:
                cout << "Tree edge";
                break;
            case 1:
                cout << "Back edge";
                break;
            case 2:
                cout << "Forward edge";
                break;
            case 3:
                cout << "Cross edge";
                break;
        }
        cout << endl;
    }

    return 0;
}
