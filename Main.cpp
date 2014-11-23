#include <sstream>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

int main()
{
    string line, command;
    Graph xy;
    
    do
    {
        cout << "> ";
        getline(cin, line);
        
        if(cin.eof()){break;}
        
        stringstream stream(line);
        
        stream >> command;
        
        string to_name, from_name, path = "Dijkstra";
        int weight = 1;
        
        if(command == "insertvert")
        {
            stream >> from_name;
            
            if(xy.insertVert(from_name))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << from_name << "already exists" << endl;
            }
        }
        else if(command == "removevert")
        {
            stream >> from_name;
            if(xy.removeVert(from_name))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << "Vertex not found" << endl;
            }
        }
        else if(command == "insertedge")
        {
            stream >> from_name >> to_name >> weight;
            
            if(xy.insertEdge(from_name, to_name, weight))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << "A couple of things could have gone wrong..." << endl;
            }
        }
        else if(command == "removeedge")
        {
            stream >> from_name >> to_name;
            
            if(xy.removeEdge(from_name, to_name))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << "A couple of things could have gone wrong..." << endl;
            }
        }
        else if(command == "clear")
        {
            xy.clearAll();
            cout << "Success" << endl;
        }
        else if(command == "reach")
        {
            stream >> from_name >> to_name;
            
            if(xy.isReachable(from_name, to_name))
            {
                cout << to_name << " is reachable from " << from_name << endl;
            }
            else
            {
                cout << to_name << " is not reachable from " << from_name << ". Or something else went wrong..." << endl;
            }
        }
        else if(command == "printconnect")
        {
            xy.print();
        }
        else if(command == "shortestpath")
        {
            stream >> from_name >> to_name >> path;
            
            if(path == "Floyd")
            {
                xy.shortestPath2(from_name, to_name);
            }
            else
            {
                xy.shortestPath(from_name, to_name);
            }
        }
        else{cout << "invalid command" << endl;}
    }while(1);
    
    return 0;
}
