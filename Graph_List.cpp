#include"Graph_List.hh"

Graph_List::Graph_List(unsigned int & vertices, unsigned int & edges):
        Vertices_Number(vertices), Edge_Number(edges)
        {
            unsigned int tmp[vertices], one=0;
            for (int i=0; i<vertices; i++)  
            {
                tmp[i]=i;
            }
            random_shuffle(tmp, tmp+50);    //Randomizing order of vertices
            for (int i=0; i<vertices; i++)
            {
                List_Neigbours[i]=nullptr;
            }
        }

Graph_List::~Graph_List() {}