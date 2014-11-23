#include "Edge.h"

//this class is so redundant but I wanted to maintain consistency
//compared to out labs


Edge::Edge(Vertex* _toVertex, int _weight)
{
    toVertex = _toVertex;
    weight = _weight;
    next = NULL;
}

void Edge::setWeight(int _weight)
{
    weight = _weight;
}
