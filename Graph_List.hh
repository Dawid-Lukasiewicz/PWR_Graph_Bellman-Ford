#include"Vertex.hh"

using namespace std;

class Graph_List : public Vertex
{
    unsigned int Vertices_Number, Edge_Number;

    Vertex *Prev=nullptr, *Next=nullptr;  
    Vertex **List_Neigbours=nullptr;
    unsigned long int *Cost;
public:
    Graph_List(unsigned int & vertices, unsigned int & edges);
    ~Graph_List();
};

// unsigned int random_number_range(unsigned int & Range)
// {
//     unsigned int numbers[Range];
//     for (int i=0; i<Range; i++)
//     {
//         numbers[i];
//     }
    
// }


