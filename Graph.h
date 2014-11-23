#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

#include "Vertex.h"

class Graph{

private:
    Vertex* head_vert;
    int vert_count;
    
    bool insertVertHelp(Vertex*& head_vert, string name);
    bool removeVertHelp(Vertex*& head_vert, string name);
    bool isReachableHelp(Vertex*& head_vert, string to);
    void clearAllHelp(Vertex*& head_vert);
    Vertex* findVert(Vertex*& head_vert, string to);
    void printHelp(Vertex*& head_vert);
    
    void Dijkstra(vector<int>& dist, vector<Vertex*>& prev, vector<Vertex*> U);
    int returnMinIndex(vector<Vertex*> U, vector<int> dist);
    int findIndex(vector<Vertex*> U, string name);
    void printPath(vector<Vertex*> U, vector<Vertex*> prev, string source, string dest);
    
    void FloydWarshall(int**& dist, Vertex***& path, vector<Vertex*>& heap);
    void printFloyd(Vertex***& path, string source, string dest, int index1, int index2);
    int getIndex(Vertex***& path, string name);
    
public:
    Graph();
    ~Graph();
    
    bool insertVert(string name);
    bool insertEdge(string from, string to, int weight);
    
    bool removeVert(string name);
    bool removeEdge(string from, string to);
    
    bool isReachable(string from, string to);

    void clearAll();
    void print();
    
    void shortestPath(string from, string to);
    
    void shortestPath2(string from, string to);
};
#endif  /* Vertex.h */
