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
    bool is_cute; 

    Vertex() {
        con_edges_tail = NULL;
        is_cute = false; 
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

    Edge() {
        end1 = NULL;
        end2 = NULL;
    }

    Edge(Vertex* v1, Vertex* v2) {
        this->end1 = v1;
        this->end2 = v2;
    }
};

Vlist* create_LL(Vlist* head1, Edge* e, int i) {
    int edgeno;

    int n;
    cin >> n;
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
        cin >> edgeno;
        Edge* temp = &e[edgeno];
        Vlist* newNode = new Vlist(temp);
        temp2->next = newNode;
        n--;

        temp2 = temp2->next;
    }
    return head1;
}

bool isBipartite(Vertex* vertex, bool isCute) {
    vertex->is_cute = isCute;

    Vlist* edges = vertex->con_edges_tail;
    while (edges != NULL) {
        Vertex* neighbor = (vertex == edges->ptr->end1) ? edges->ptr->end2 : edges->ptr->end1;
        
        if (neighbor->is_cute == isCute) {
            return false; 
        }

        if (!neighbor ->is_cute && isBipartite(neighbor, !isCute)) {
            return false;
        }

        edges = edges->next;
    }

    return true;
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
        cout << "enter 1st vertex no., 2nd vertex no." << i << endl;
        cin >> k1 >> k2;
        e[i] = Edge(&vertices[k1], &vertices[k2]);
    }

    for (int i = 0; i < numVertices; i++) {
        Vlist* head1 = NULL;
        vertices[i].con_edges_tail = create_LL(head1, e, i);
    }

    for (int i = 0; i < numVertices; i++) {
        if (!vertices[i].is_cute && !isBipartite(&vertices[i], true)) {
            cout << "Yes there will be rivalries" << endl;
            return 0;
        }
    }

    cout << "No there will be no rivalries" << endl;

    return 0;
}
