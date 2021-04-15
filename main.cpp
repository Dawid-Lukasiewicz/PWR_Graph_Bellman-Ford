#include<cstdlib>
#include<iostream>
#include"Graph_Matrix.hh"

#define V_NUMBER 5

int ** generate_g_matrix(unsigned int & vertices)
{
    int **matrix=new int*[vertices];
    for (int i=0; i<vertices; i++)
    {
        matrix[i]=new int[vertices];
    }
    return matrix;
}

void insert_to_file(unsigned int vertices, unsigned int edges, fstream & to_file)
{
    to_file.open("data.txt", std::fstream::app);

    to_file<<edges<<"   "<<vertices<<"  "<<rand()%vertices<<endl;
    
}

void generate_data(fstream & to_file)
{
    unsigned int vertices[V_NUMBER]={10,50,100,500,1000};
    unsigned int max_number_edge[V_NUMBER];
    unsigned int edges[V_NUMBER][4];
    unsigned int filling[4]={25,50,75,100};

    for (int v=0; v<V_NUMBER; v++)
    {
        max_number_edge[v]=vertices[v]*(vertices[v]-1)/2;
        for (int f=0; f<4; f++)
        {
            edges[v][f]=filling[f]*max_number_edge[v]/100;
            for (int i=0; i<100; i++)
                insert_to_file(vertices[v],edges[v][f], to_file);
        }
    }
    
}

int main()
{
    
    return 0;
}