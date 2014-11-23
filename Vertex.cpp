#include "Vertex.h"

Vertex::Vertex(string _name)
{
    name = _name;
    edgeCount = 0;
    visited = false;
    head_edge = NULL;
    next = NULL;
}

Vertex::~Vertex()
{
    removeAllEdges(head_edge);
}

string Vertex::getName()
{
    return name;
}

bool Vertex::insertEdge(Edge*& head_edge, Vertex* to_vert, int weight)
{
    //same as insert vertex
    if(head_edge == NULL)
    {
        head_edge = new Edge(to_vert, weight);
        return true;
    }
    if((head_edge->toVertex)->name == to_vert->name)
    {
        return false;
    }
    else
    {
        return insertEdge(head_edge->next, to_vert, weight);
    }
}

bool Vertex::removeEdge(Edge*& head_edge, Vertex* to_vert)
{
    //same as insert vertex
    if(head_edge != NULL)
    {
        if((head_edge->toVertex)->name == to_vert->name)
        {
            Edge* delPtr = head_edge;
            
            head_edge = head_edge->next;
            
            delete(delPtr);
            
            return true;
        }
        else
        {
            return removeEdge(head_edge->next, to_vert);
        }
    }
    else
    {
        return false;
    }
}

void Vertex::removeAllEdges(Edge*& head_edge)
{
    //deleting all edges
    if(head_edge != NULL)
    {
        removeAllEdges(head_edge->next);
        delete head_edge;
        head_edge = NULL;
    }
    
}

void Vertex::printEdges()
{
    printEdgesHelp(head_edge);
}

void Vertex::printEdgesHelp(Edge*& head_edge)
{
    //print formatting for printing edges
    if(head_edge != NULL)
    {
        cout << "\t" << (head_edge->toVertex)->getName()
        << "(" << head_edge->weight << ")";
        printEdgesHelp(head_edge->next);
    }
}

int Vertex::findWeight(Vertex*& to)
{
    Edge* temp = head_edge;
    
    while(temp != NULL)
    {
        if(temp->toVertex->getName() == to->getName())
        {
            return temp->getWeight();
        }
        
        temp = temp->next;
    }
    
    return 1000;
}
