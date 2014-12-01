#include "Graph.h"

void Graph::span(string source)
{
    Vertex* source_vert = findVert(head_vert, source);
    
    if(source_vert == NULL)
    {
        cout << "Source not found" << endl;
        return;
    }
    
    vector<int> dist;
    vector<Vertex*> U;
    
    dist.push_back(0);
    U.push_back(source_vert);
    
    Vertex* temp_head = head_vert;
    while(temp_head != NULL)
    {
        //already added the source
        if(temp_head->getName() != source)
        {
            dist.push_back(INT_MAX);
            U.push_back(temp_head);
        }
        
        //set flags to false (unvisited)
        temp_head->visited = false;
        temp_head = temp_head->next;
    }
    
    Prims(U, dist);
    
    //sum Prims
    int sum = 0;
    for(int i = 0; i < dist.size(); i++)
    {
        //cout << dist[i] << endl;
        sum += dist[i];
    }
    
    cout << endl;
    
    cout << "Spanning path has length of: " << sum << endl;
}

void Graph::Prims(vector<Vertex*>& U, vector<int>& dist)
{
    vector<Vertex*> F;
    int size = U.size();
    F.push_back(U[0]);
    U[0]->visited = true;
    
    cout << endl;
    
    while(F.size() < size)
    {
        int index = getMinIndex(U, F, dist);
        U[index]->visited = true;
        F.push_back(U[index]);
        cout << U[index]->getName() << endl;
        
        //getMinIndex() (below) ended up doing all the work...
        /*
        Edge* temp_edge_head = U[index]->head_edge;
        while(temp_edge_head != NULL)
        {
            int edge_vert_index = findIndex(U, temp_edge_head->toVertex->getName());
            
            if(temp_edge_head->weight < dist[edge_vert_index])
                dist[edge_vert_index] = temp_edge_head->weight;
            
            temp_edge_head = temp_edge_head->next;
        }
         */
    }
}

//this function does it all... awkward
int Graph::getMinIndex(vector<Vertex*>& U, vector<Vertex*>& F, vector<int>& dist)
{
    string name_to_find;
    int curr_weight = INT_MAX;
    for(int i = 0; i < F.size(); i++)
    {
        Edge* temp_head = F[i]->head_edge;
        while(temp_head != NULL)
        {
            //think about < vs <=
            if(temp_head->weight < curr_weight && temp_head->toVertex->visited == false)
            {
                curr_weight = temp_head->weight;
                name_to_find = (temp_head->toVertex)->getName();
            }
            
            temp_head = temp_head->next;
        }
    }
    
    //findIndex() is implemented in s_paths.cpp (from dijkstras)
    int retInd = findIndex(U, name_to_find);
    dist[retInd] = curr_weight;
    
    return retInd;
}
