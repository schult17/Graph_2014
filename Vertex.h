#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <iostream>
#include <string>
#include <limits>

using namespace std;

#include "Edge.h"

class Graph;

class Vertex{

private:
    string name;
    int edgeCount;
    bool visited;
    Edge* head_edge;
    Vertex* next;
    
    bool insertEdge(Edge*& head_edge, Vertex* to_vert, int weight);
    bool removeEdge(Edge*& head_edge, Vertex* to_vert);
    
    void removeAllEdges(Edge*& head_edge);
    
    void printEdgesHelp(Edge*& head_edge);
    
public:
    Vertex(string _name);
    ~Vertex();
    string getName();
    void printEdges();
    int findWeight(Vertex*& to);
    
    friend class Graph;
};

#endif  /* Vertex.h */
