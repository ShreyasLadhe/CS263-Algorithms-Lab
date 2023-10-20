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
    bool isDirected; 

    Edge() {
        end1 = NULL;
        end2 = NULL;
        isDirected = false; 
    }

    Edge(Vertex* v1, Vertex* v2, bool directed) {
        this->end1 = v1;
        this->end2 = v2;
        this->isDirected = directed;
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

bool isCyclicDFS(Vertex* vertices, int currentVertex, bool* visited, bool* recStack) {
    if (!visited[currentVertex]) {
        visited[currentVertex] = true;
        recStack[currentVertex] = true;

        Vlist* adj = vertices[currentVertex].con_edges_tail;
        while (adj != NULL) {
            int index = adj->ptr->isDirected ? adj->ptr->end2 - vertices : adj->ptr->end1 - vertices;
            if (!visited[index] && isCyclicDFS(vertices, index, visited, recStack)) {
                return true;
            } else if (recStack[index]) {
                return true;
            }
            adj = adj->next;
        }
    }
    recStack[currentVertex] = false;
    return false;
}

bool isCyclic(Vertex* vertices, int numVertices) {
    bool* visited = new bool[numVertices];
    bool* recStack = new bool[numVertices];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && isCyclicDFS(vertices, i, visited, recStack)) {
            delete[] visited;
            delete[] recStack;
            return true;
        }
    }

    delete[] visited;
    delete[] recStack;
    return false;
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

    if (isCyclic(vertices, numVertices)) {
        cout << "The graph contains cycles." << endl;
    } else {
        cout << "The graph does not contain cycles." << endl;
    }

    return 0;
}
