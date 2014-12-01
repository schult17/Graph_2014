#include "Graph.h"

//Read below if you want to see a shortest paths example(not needed this semester)
//both dijkstras and floyd algorithms implemented (chosen by user)

void Graph::shortestPath(string from, string to)
{
    //this is a set up function
    
    //try and find both the source and destination vertex
    Vertex* source = findVert(head_vert, from);
    Vertex* dest = findVert(head_vert, to);
    
    //make sure both are found
    if(source == NULL)
    {
        cout << "Source not found!" << endl;
        return;
    }
    else if(dest == NULL)
    {
        cout << "Destination not found" << endl;
        return;
    }
    
    //make sure it is reachable before finding the shortest path
    //if we didn't do this, the distance would be INT_MAX (35 535? maybe)
    if(!isReachable(from, to))
    {
        cout << "The destination is not reachable from the source" << endl;
        return;
    }
    
    //easy case
    if(source->getName() == dest->getName())
    {
        cout << "Shortest Distance from " << from << " to "
        << to << " is 0" << endl;
        return;
    }
    
    //lets make some vectors (easier to work with than linked lists)
    vector<int> dist;   //this will store the distances
    vector<Vertex*> prev;   //this will track the vertices we have visted
    vector<Vertex*> U;  //heap of vertices (marked visited = true once visited)
    
    prev.push_back(source); //add the source
    U.push_back(source);
    dist.push_back(0);  //distance from source to source is 0
    
    //note that dist and prev have to corellate//
    
    //loop over all vertices and add them to respective vectors
    Vertex* temp_head = head_vert;
    while(temp_head != NULL)
    {
        //already added the source
        if(temp_head->getName() != from)
        {
            dist.push_back(INT_MAX);
            prev.push_back(NULL);
            U.push_back(temp_head);
        }
        
        //set flags to false (unvisited)
        temp_head->visited = false;
        
        temp_head = temp_head->next;
    }
    
    
    /*Dijkstra's algorithm is greedy, it says: okay, you want to know the
     *shortest distance form source -> destination? well I will find you
     *the shorest distance from source -> ALL THE OTHER VERTICES, then I will
     *give you a list of all the places I went and the distances and you can
     *figure out what one you want... It seems horrible but this algorithm
     *(excluding some set up time) in almost LINEAR TIME! Whatttttt, Dynamic
     *programming FTW!*/
    
    Dijkstra(dist, prev, U);
    
    int dest_index = findIndex(U, to);
    
    cout << "Shortest Distance from " << from << " to "
    << to << " is " << dist[dest_index] << endl;
    
    cout << "Path Taken:" << endl;
    
    printPath(U, prev, from, to);
}

void Graph::Dijkstra(vector<int>& dist,
                     vector<Vertex*>& prev,
                     vector<Vertex*> U)
{
    //this vector stores the visited vertices
    vector<Vertex*> F;
    int size = U.size();
    
    //when all are visited (from source) we are done
    while(F.size() < size)
    {
        //In the vector U, find the smallest distance to source
        //first iteration, this will be 0 (source is always first)
        int index = returnMinIndex(U, dist);
        
        //the current vertex is the one we found in U (smallest)
        Vertex* curr = U[index];
        
        //queue the current vertex
        F.push_back(curr);
        
        //loop over all the edges of the current vertex
        Edge* temp_edge_head = curr->head_edge;
        while(temp_edge_head != NULL)
        {
            //find the index (in U) of the vertex the current edge points to
            int edge_vert_index = findIndex(U, temp_edge_head->toVertex->getName());
            
            //RELAXATION: kind of hard to explain. If the distance from the
            //current vertex (index) + the weight of the edge to the vertex
            //pointed to by the edge is less than the distance to the vertex
            //pointed to by the edge curently (why we set them to MAX_INT
            //at the start), then thisn path is shorter, make this distance
            //the new distance, and track the pointer (curr)
            if(dist[index] + temp_edge_head->weight < dist[edge_vert_index])
            {
                dist[edge_vert_index] = dist[index] + temp_edge_head->weight;
                prev[edge_vert_index] = curr;
            }
            
            //move to the next edge
            temp_edge_head = temp_edge_head->next;
        }
    }
}

int Graph::returnMinIndex(vector<Vertex*> U, vector<int> dist )
{
    int smallest_index = 0;
    int maxDistance = INT_MAX;
    
    //loops over all the vectors in U and returns the index of the vertex with
    //smallest distance to the source
    for(int i = 0; i < U.size(); i++)
    {
        if(dist[i] < maxDistance && (U[i])->visited == false)
        {
            smallest_index = i;
        }
    }
    
    //marks the vertex as visited
    U[smallest_index]->visited = true;
    return smallest_index;
}


int Graph::findIndex(vector<Vertex*> U, string name)
{
    //returns the index of the given vertex (by name) in U
    int ret_index;
    for(int i = 0; i < U.size(); i++)
    {
        if(U[i]->getName() == name)
        {
            ret_index = i;
            break;
        }
    }
    
    return ret_index;
}

void Graph::printPath(vector<Vertex*> U,
                      vector<Vertex*> prev,
                      string source,
                      string dest)
{
    vector<Vertex*> path;
    Vertex* curr = NULL;
    
    //prev stores the path we took to get to each vertex in
    //reverse order (could have made a stack, but didn't)
    do
    {
        //find the index of the destination
        int curr_index = findIndex(U, dest);
        curr = U[curr_index];
        
        //temp vector
        vector<Vertex*>::iterator it;
        
        //move iterator to beginning
        it = path.begin();
        
        //insert the current pointer (into the front) into the
        //vector (this is a stack...)
        path.insert(it, curr);
        
        //change the name of dest to the vertex we just found in U.
        //without understanding how the pointer are stored in prev, this
        //algorithm is a little weird...again, if you care, look it up
        //online
        dest = prev[curr_index]->getName();
    }while(curr->getName() != source);
    
    //print that path!
    for(int i = 0; i < path.size(); i++)
    {
        cout << (path[i])->getName();
        
        if(i != path.size() - 1)
            cout << " -> ";
    }
    
    cout << endl;
}

void Graph::shortestPath2(string from, string to)
{
    //try and find both the source and destination vertex
    Vertex* source = findVert(head_vert, from);
    Vertex* dest = findVert(head_vert, to);
    
    //make sure both are found
    if(source == NULL)
    {
        cout << "Source not found!" << endl;
        return;
    }
    else if(dest == NULL)
    {
        cout << "Destination not found" << endl;
        return;
    }
    
    //make sure it is reachable before finding the shortest path
    //if we didn't do this, the distance would be INT_MAX (35 535? maybe)
    if(!isReachable(from, to))
    {
        cout << "The destination is not reachable from the source" << endl;
        return;
    }
    
    //easy case
    if(source->getName() == dest->getName())
    {
        cout << "Shortest Distance from " << from << " to "
        << to << " is 0" << endl;
        return;
    }
    
    vector<Vertex*> vertices;
    Vertex* temp_head = head_vert;
    
    int source_index = 0;
    int dest_index = 0;
    int i = 0;
    while(temp_head != NULL)
    {
        if(temp_head->getName() == from)
            source_index = i;
        else if(temp_head->getName() == to)
            dest_index = i;
        
        vertices.push_back(temp_head);
        temp_head = temp_head->next;
        i++;
    }
    
    int** distance = new int*[vert_count];
    Vertex*** paths = new Vertex**[vert_count];
    
    for(int i = 0; i < vert_count; i++)
    {
        distance[i] = new int[vert_count];
        paths[i] = new Vertex*[vert_count];
        
        for(int j = 0; j < vert_count; j++)
        {
            if(i == j)
            {
                distance[i][j] = 0;
            }
            else
            {
                distance[i][j] = vertices[i]->findWeight(vertices[j]);
            }
            
            paths[i][j] = vertices[i];
        }
    }
    
    FloydWarshall(distance, paths, vertices);
    
    cout << "Shortest Distance from " << from << " to "
    << to << " is " << distance[source_index][dest_index] << endl;
    
    cout << "Path taken: ";
    printFloyd(paths, from, to, source_index, dest_index);
    cout << endl;
    
    for(int i = 0; i < vert_count; i++)
    {
        delete[] distance[i];
        delete[] paths[i];
    }
    
    delete[] distance;
    delete[] paths;
    
    distance = NULL;
    paths = NULL;
}

void Graph::FloydWarshall(int**& dist, Vertex***& paths,
                          vector<Vertex*>& heap)
{
    for(int k = 0; k < vert_count; k++)
    {
        for(int i = 0; i < vert_count; i++)
        {
            for(int j = 0; j < vert_count; j++)
            {
                if(dist[i][j] > (dist[i][k] + dist[k][j]))
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    paths[i][j] = paths[k][i];
                }
            }
        }
    }
}

void Graph::printFloyd(Vertex***& path, string source, string dest, int index1, int index2)
{
    vector<string> out_path;
    
    out_path.push_back(dest);
    
    while(1)
    {
        string name = path[index1][index2]->getName();
        
        if(name == source)
            break;
        else
            out_path.push_back(name);
        
        index2 = getIndex(path, name);
    }
    
    out_path.push_back(source);
    
    for(int i = (out_path.size() - 1); i >= 0; i--)
    {
        cout << out_path[i];
        
        if(i != 0)
            cout << " -> ";
        
    }
    
    cout << endl;
}

int Graph::getIndex(Vertex***& path, string name)
{
    Vertex* temp = head_vert;
    int index = 0;
    while(temp != NULL)
    {
        if(temp->getName() == name)
            break;
        
        index++;
        temp = temp->next;
    }
    
    return index;
}
