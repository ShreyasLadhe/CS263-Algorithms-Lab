#include <iostream>
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

        temp2=temp2->next;
    }
    return head1;
}

class CustomQueue {
private:
    int front, rear, size;
    Vertex** elements;

public:
    CustomQueue(int size) {
        front = -1;
        rear = -1;
        this->size = size;
        elements = new Vertex*[size];
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return (front == 0 && rear == size - 1) || (front == rear + 1);
    }

    void enqueue(Vertex* element) {
        if (isFull()) {
            cout << "Queue is full." << endl;
        } else {
            if (front == -1) front = 0;
            rear = (rear + 1) % size;
            elements[rear] = element;
        }
    }

    Vertex* dequeue() {
        Vertex* element;
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return NULL;
        } else {
            element = elements[front];
            if (front == rear) {
                front = -1;
                rear = -1;
            } else {
                front = (front + 1) % size;
            }
        }
        return element;
    }
};

bool BFS(Vertex* start, Vertex* end) {
    CustomQueue queue(5);
    queue.enqueue(start);
    start->visited = true;

    while (!queue.isEmpty()) {
        Vertex* current = queue.dequeue();

        if (current == end) {
            return true; // Path found
        }

        Vlist* edgeList = current->con_edges_tail;
        while (edgeList != NULL) {
            Vertex* neighbor = (current == edgeList->ptr->end1) ? edgeList->ptr->end2 : edgeList->ptr->end1;
            if (!neighbor->visited) {
                neighbor->visited = true;
                neighbor->con_edges_tail = edgeList; // Store the edge leading to this neighbor
                queue.enqueue(neighbor);
            }
            edgeList = edgeList->next;
        }
    }

    return false; // No path found
}

void printShortestPath(Vertex* start, Vertex* end) {
    if (!BFS(start, end)) {
        cout << "No path found between " << start->data << " and " << end->data << endl;
        return;
    }

    cout << "Shortest path between " << start->data << " and " << end->data << " is: ";
    while (end != start) {
        cout << end->data;
        end = (end == end->con_edges_tail->ptr->end1) ? end->con_edges_tail->ptr->end2 : end->con_edges_tail->ptr->end1;
        if (end != start) cout << " -> ";
    }
    cout << start->data << endl;
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

    char startVertex, endVertex;
    cout << "Enter the starting vertex: ";
    cin >> startVertex;
    cout << "Enter the ending vertex: ";
    cin >> endVertex;

    Vertex* start = NULL;
    Vertex* end = NULL;

    for (int i = 0; i < 5; i++) {
        if (vertices[i].data == startVertex) start = &vertices[i];
        if (vertices[i].data == endVertex) end = &vertices[i];
    }

    if (start != NULL && end != NULL) {
        printShortestPath(start, end);
    } else {
        cout << "Starting or ending vertex not found." << endl;
    }

    return 0;
}
