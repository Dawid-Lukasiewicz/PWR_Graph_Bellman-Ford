#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
// #include"Vertex.hh"

using namespace std;

class Graph_Matrix
{
private:
    unsigned int Vertices_Number, Edge_Number, Starting_Point;
    unsigned int **Matrix;

public:
    Graph_Matrix(unsigned int & vertices, unsigned int & edges, unsigned int & start);
    Graph_Matrix(ifstream& input);  //From file
    ~Graph_Matrix();
    unsigned int & set_Vertices_Number();
    const unsigned int & get_Vertices_Number();
    unsigned int & set_Edge_Number();
    const unsigned int & get_Edge_Number();
    void show_matrix();

    // unsigned int & get_random_value(unsigned int & const vertices);
};

Graph_Matrix::Graph_Matrix(unsigned int & vertices, unsigned int & edges, unsigned int & start)
    :Vertices_Number(vertices), Edge_Number(edges), Starting_Point(start)
{
    Matrix=new unsigned int*[Vertices_Number];
    for(int i=0; i<Vertices_Number; i++)
        Matrix[i]=new unsigned int[Vertices_Number];

    unsigned int tmp=0;
    for(int i=0; i<Vertices_Number; i++)
    {
        for(int j=tmp; j<Vertices_Number; j++)
        {
            Matrix[i][j]=0;
            Matrix[j][i]=0;
        }
        tmp++;
    }
}

Graph_Matrix::Graph_Matrix(ifstream& input)
{
    if (!input.is_open())
    {
        cout<<"File not opened"<<endl;
        exit(-1);
    }
    
    input>>set_Edge_Number()>>set_Vertices_Number()>>Starting_Point;
    // cout<<"Edge: "<<get_Edge_Number()<<"Vertices: "<<get_Vertices_Number()<<endl;
    Matrix=new unsigned int*[Vertices_Number];
    for(int i=0; i<Vertices_Number; i++)
        Matrix[i]=new unsigned int[Vertices_Number];
    
    unsigned int tmp=0;
    for(int i=0; i<Vertices_Number; i++)
    {
        
        for(int j=tmp; j<Vertices_Number; ++j)
        {
            Matrix[i][j]=0;
            Matrix[j][i]=0;
        }
        tmp++;
    }

    unsigned int v1,v2,weight;
    for(int i=0; i<Edge_Number; i++)
        {
            input>>v1>>v2>>weight;
            // cout<<"v1: "<<v1<<endl;
            // cout<<"v2: "<<v2<<endl;
            // cout<<"weight: "<<weight<<endl;
            Matrix[v1][v2]=weight;
            Matrix[v2][v1]=weight;
        }
}

Graph_Matrix::~Graph_Matrix()
{}

unsigned int & Graph_Matrix::set_Vertices_Number()
{
    return Vertices_Number;
}

const unsigned int & Graph_Matrix::get_Vertices_Number()
{
    return Vertices_Number;
}

unsigned int & Graph_Matrix::set_Edge_Number()
{
    return Edge_Number;
}

const unsigned int & Graph_Matrix::get_Edge_Number()
{
    return Edge_Number;
}

void Graph_Matrix::show_matrix()
{
    for (int i=0; i<Vertices_Number; i++)
    {
        for (int j=0; j<Vertices_Number; j++)
        {
            cout<<Matrix[i][j]<<"  ";
        }
        cout<<endl;
    }
    
}