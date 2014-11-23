#ifndef _EDGE_H_
#define _EDGE_H_

#include <iostream>

using namespace std;

class Vertex;

class Edge{
private:
    Vertex* toVertex;
    int weight;
    Edge* next;

public:
    Edge(Vertex* _toVertex, int weight);
    
    void setWeight(int _weight);
    int getWeight()
    {
        return weight;
    }
    
    friend class Vertex;
    friend class Graph;
};

#endif  /* Edge.h */
