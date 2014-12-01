#include "Graph.h"

Graph::Graph()
{
    head_vert = NULL;
    vert_count = 0;
}

Graph::~Graph()
{
    clearAll();
}

bool Graph::insertVert(string name)
{
    return insertVertHelp(head_vert, name);
}

bool Graph::insertVertHelp(Vertex*& head_vert, string name)
{
    //recursive insert function (queue like, insert at end
    //if it does not exist)
    if(head_vert == NULL)
    {
        head_vert = new Vertex(name);
        vert_count += 1;
        return true;
    }
    else if(head_vert->getName() == name)
    {
        return false;
    }
    else
    {
        return insertVertHelp(head_vert->next, name);
    }
    
}

bool Graph::insertEdge(string from, string to, int weight)
{
    //first ty and find both vertices
    Vertex* from_vert = findVert(head_vert, from);
    Vertex* to_vert = findVert(head_vert, to);
    
    //check if both vertices exist
    if(from_vert == NULL || to_vert == NULL)
    {
        return false;
    }
    else
    {
        bool state1 = false;
        bool state2 = true;
        
        state1 = from_vert->insertEdge(from_vert->head_edge, to_vert, weight);
        
        //*******************************************************************//
        //****start comment below for directed, uncomment for undirected*****//
        
        state2 = false;
        if(state1)
            state2 = to_vert->insertEdge(to_vert->head_edge, from_vert, weight);
        
        //in case we inserted the first edge, but an error occured in the second,
        //delete the first edge made - this should never happen, but in for safety.
        if(!state2)
            from_vert->removeEdge(from_vert->head_edge, to_vert);
        
        //****end comment above for directed, uncomment for undirected!****//
        //*******************************************************************//
            
        return (state1 && state2);
    }
}

bool Graph::removeVert(string name)
{
    //find the vertex to be deleted
    Vertex* del_vert = findVert(head_vert, name);
    
    if(del_vert == NULL) //vertex does not exist
    {
        return false;
    }
    else  //we have found the vertex to delete
    {
        Vertex* temp_head_vert = head_vert;
        string del_name = del_vert->getName();
     
        // before deleting the vertex, we must delete all the edges,
        //in the other vertices that point to this one
        while(temp_head_vert != NULL)
        {
            //save some time, we are deleting del_name anyway
            if(temp_head_vert->getName() != del_name)
            {
                string curr_name = temp_head_vert->getName();
                removeEdge(curr_name, del_name);
            }
            
            temp_head_vert = temp_head_vert->next;
        }
        
        //once all the edges into this vertex are deleted, delete the vertex
        removeVertHelp(head_vert, name);
        
        vert_count -= 1;
        return true;
    }
}

bool Graph::removeVertHelp(Vertex*& head_vert, string name)
{
    //generic recursive delete function, kind of like the one child
    //case in a tree
    if(head_vert != NULL)
    {
        if(head_vert->getName() == name)
        {
            //if we delete the last one, head_vert->next == NULL
            Vertex* delPtr = head_vert;
            head_vert = head_vert->next;
            
            delete(delPtr);
            return true;
        }
        else
        {
            return removeVertHelp(head_vert->next, name);
        }
    }
    else //vertex not found
    {
        return false;
    }
}

bool Graph::removeEdge(string from, string to)
{
    //find both vertices
    Vertex* from_vert = findVert(head_vert, from);
    Vertex* to_vert = findVert(head_vert, to);
    
    //make sure both exist
    if(from_vert == NULL || to_vert == NULL)
    {
        return false;
    }
    else
    {
        //note: this is not a recursive call to this function
        //it calls removeEdge() in Vertex.cpp, from_vert is a
        //vertex, not graph... bad nameing.
        return from_vert->removeEdge(from_vert->head_edge, to_vert);
    }
}

bool Graph::isReachable(string from, string to)
{
    //find the vertices
    Vertex* temp_head = head_vert;
    Vertex* start_vert = NULL;
    
    //initialize all teh visited flags to false, and
    //find the starting vertice
    while(temp_head != NULL)
    {
        temp_head->visited = false;
        
        if(temp_head->getName() == from)
        {
            start_vert = temp_head;
        }
        
        temp_head = temp_head->next;
    }
    
    //check to make sure we found the start
    if(start_vert == NULL)
    {
        return false;
    }
    
    return isReachableHelp(start_vert, to);
}

bool Graph::isReachableHelp(Vertex*& start_vert, string to)
{
    //if we have already visited this vertex, it is not reachable
    //          reference (1)
    if(start_vert->visited)
    {
        return false;
    }
    
    //if the name of this vertex matches the destination, we are there
    //          reference (2)
    if(start_vert->getName() == to)
    {
        return true;
    }
    
    //mark this vertex as visited
    start_vert->visited = true;
    
    //temp pointer to edges of this vertex
    Edge* temp_edge_head = start_vert->head_edge;
    
    //loop over all the edges in this vertex
    while(temp_edge_head != NULL)
    {
        /*check if the destination is reachable from any of this
         *vertex's edges. We can just return isReachableHelp(),
         *because we don't want to return yet if its false.
         *This recursive will move through all of the edges, and the 
         *edge's edges until we have either visited the vertex already
         *(reference (2)), or until we have found it (reference (1)),
         *only then will it move to the next edge in our list*/
        if(isReachableHelp(temp_edge_head->toVertex, to))
        {
            return true;
        }
        
        //move to the next vertex.
        temp_edge_head = temp_edge_head->next;
    }
    
    //if we get here, we get to the end of the edges of our found vertex
    //so we cannot reach the destitnation (we would only get here
    //in a DAG situation (directed acyclic graph)
    return false;
}

void Graph::clearAll()
{
    vert_count = 0;
    clearAllHelp(head_vert);
}

void Graph::clearAllHelp(Vertex*& head_vert)
{
    //deletes all vertices, the deletion of the edges is handled
    //by another function called in the vertices destructor
    if(head_vert != NULL)
    {
        clearAllHelp(head_vert->next);
        
        delete(head_vert);
        head_vert = NULL;
    }
}

Vertex* Graph::findVert(Vertex*& head_vert, string name)
{
    if(head_vert == NULL)
    {
        return head_vert;
    }
    else if(head_vert->getName() == name)
    {
        return head_vert;
    }
    else
    {
        return findVert(head_vert->next, name);
    }
}

void Graph::print()
{
    printHelp(head_vert);
}

void Graph::printHelp(Vertex*& head_vert)
{
    //print the vertex and its edges
    if(head_vert != NULL)
    {
        cout << head_vert->getName() << ":";
        head_vert->printEdges();
        cout << "\n";
        printHelp(head_vert->next);
    }
}
