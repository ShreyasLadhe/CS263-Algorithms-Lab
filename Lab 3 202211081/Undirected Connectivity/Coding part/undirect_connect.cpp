#include <iostream>
#include <queue>

using namespace std;

class Vertex;
class Vlist;
class Edge;

class Vertex {
public:
    char data;
    Vlist* con_edges_tail;
    bool visited;

    Vertex() {
        con_edges_tail = NULL;
        visited = false;
    }

    Vertex(char data) {
        this->data = data;
        this->con_edges_tail = NULL;
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

        temp2 = temp2->next;
    }
    return head1;
}

void BFS(Vertex vertices[], int startVertex, int numVertices, char disconnectedComponents[], int& disconnectedCount) {
    bool visited[numVertices] = {false};
    int parent[numVertices];
    bool isDisconnected = false;

    cout << "BFS starting from vertex " << vertices[startVertex].data << ":" << endl;
    visited[startVertex] = true;
    parent[startVertex] = -1;

    queue<int> q;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertexIndex = q.front();
        q.pop();

        Vertex* currentVertex = &vertices[currentVertexIndex];
        cout << "Visited: " << currentVertex->data;

        if (parent[currentVertexIndex] != -1) {
            int parentIndex = parent[currentVertexIndex];
            cout << " (via " << vertices[parentIndex].data << ")";
        }
        cout << endl;

        Vlist* edgeList = currentVertex->con_edges_tail;
        while (edgeList != NULL) {
            Vertex* neighbor = (currentVertex == edgeList->ptr->end1) ? edgeList->ptr->end2 : edgeList->ptr->end1;
            int neighborIndex = neighbor - &vertices[0];
            if (!visited[neighborIndex]) {
                visited[neighborIndex] = true;
                parent[neighborIndex] = currentVertexIndex;
                q.push(neighborIndex);
            }
            edgeList = edgeList->next;
        }

        if (q.empty()) {
            // If there are unvisited nodes, start BFS from them for disconnected components
            isDisconnected = false;
            for (int i = 0; i < numVertices; i++) {
                if (!visited[i]) {
                    isDisconnected = true;
                    disconnectedComponents[disconnectedCount++] = vertices[i].data;
                    q.push(i);
                    break;
                }
            }
        }
    }

    if (isDisconnected) {
        cout << "Disconnected component starting from node " << disconnectedComponents[disconnectedCount - 1] << ":" << endl;
        for (int i = disconnectedCount - 1; i >= 0; i--) {
            cout << disconnectedComponents[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    Vertex vertices[5];
    Edge e[7];

    for (int i = 0; i < 5; i++) {
        char data;
        cout << "enter vertex data: ";
        cin >> data;
        vertices[i] = Vertex(data);
    }

    for (int i = 0; i < 7; i++) {
        int k1, k2;
        cout << "enter 1st vertex no. and 2nd vertex no. for edge " << i << endl;
        cin >> k1 >> k2;
        e[i] = Edge(&vertices[k1], &vertices[k2]);
    }

    for (int i = 0; i < 5; i++) {
        Vlist* head1 = NULL;
        vertices[i].con_edges_tail = create_LL(head1, e, i);
    }

    for (int i = 0; i < 5; i++) {
        cout << "for vertex " << vertices[i].data << endl;
        Vlist* ptr2 = vertices[i].con_edges_tail;
        while (ptr2 != NULL) {
            cout << "edges are (" << ptr2->ptr->end1->data << "," << ptr2->ptr->end2->data << ")" << endl;
            ptr2 = ptr2->next;
        }
    }

    char disconnectedComponents[5]; // Assuming there are at most 5 disconnected components
    int disconnectedCount = 0;
    for (int i = 0; i < 5; i++) {
        if (!vertices[i].visited) {
            BFS(vertices, i, 5, disconnectedComponents, disconnectedCount);
        }
    }

    return 0;
}
