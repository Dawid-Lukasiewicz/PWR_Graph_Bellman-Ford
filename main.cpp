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
    
    to_file.open("data.txt", std::fstream::app);    //Open file with append mode

    to_file<<edges<<"   "<<vertices<<"  "<<rand()%vertices<<endl;   //Number of edges, vertices and a starting point
    
    for (int i=0; i<edges-1 && i<vertices-1 ; i++)
    {
        to_file<<i<<"   "<<i+1<<"   "<<rand()%100+1<<endl;      //Generating edges of random weight value
    }

    unsigned int number_of_vertices=vertices;
    unsigned int left_to_fill=vertices-edges;
    unsigned int count=0;
    while(count<left_to_fill)       //Inserting the leff amount of edges
    {
        unsigned int count_2=0;
        while (count<left_to_fill && count_2<number_of_vertices-1)
        {
            to_file<<number_of_vertices-1<<"    "<<count_2<<"   "<<rand()%10+1<<endl;

            count++;
            count_2++;
        }
        left_to_fill--;
    }
    to_file.close();
    
}

void generate_data(fstream & to_file)
{
    unsigned int vertices[V_NUMBER]={10,50,100,500,1000};   //Sizes of graph given in project
    unsigned int max_number_edge[V_NUMBER];     //Max limit of edges possible in given graph
    unsigned int edges[V_NUMBER][4];            //Amount of edges depending od filling od graph
    unsigned int filling[4]={25,50,75,100};     //Percent of filling given in project

    for (int v=0; v<V_NUMBER; v++)      //V_NUMBER of sizes of graph
    {
        max_number_edge[v]=vertices[v]*(vertices[v]-1)/2;   //Find the max amount of possible edges
        for (int f=0; f<4; f++)     //4 different number of fillings of graph
        {
            edges[v][f]=filling[f]*max_number_edge[v]/100;      //Number of edges given by filling percentage
            for (int i=0; i<100; i++)       //100 different instances of the same type of graph
                insert_to_file(vertices[v],edges[v][f], to_file);  
        }
    }
    
}

int main()
{
    
    return 0;
}