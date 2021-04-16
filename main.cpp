#include<cstdlib>
#include<iostream>
#include"Graph_Matrix.hh"

#define V_NUMBER 5
#define INSTANCES 2
// int ** generate_g_matrix(unsigned int & vertices)
// {
//     int **matrix=new int*[vertices];
//     for (int i=0; i<vertices; i++)
//     {
//         matrix[i]=new int[vertices];
//     }
//     return matrix;
// }

void insert_to_file(unsigned int vertices, unsigned int edges, fstream & to_file)
{
    
    to_file.open("data.txt", std::fstream::app);    //Open file with append mode

    to_file<<edges<<"   "<<vertices<<"  "<<rand()%vertices<<endl;   //Number of edges, vertices and a starting point
    
    for (int i=0; i<edges-1 && i<vertices-1 ; i++)
    {
        to_file<<i<<"   "<<i+1<<"   "<<rand()%100+1<<endl;      //Generating edges of random weight value
    }

    unsigned int number_of_vertices=vertices;
    unsigned int left_to_fill=edges-vertices+1;
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
        number_of_vertices--;
    }
    to_file.close();
    
}

void generate_data(fstream & to_file)
{
    unsigned int vertices[V_NUMBER]={10,50,100,500,1000};   //Sizes of graph given in project
    unsigned int max_number_edge[V_NUMBER];     //Max limit of edges possible in given graph
    unsigned int edges[V_NUMBER][4];            //Amount of edges depending od filling od graph
    unsigned int filling[4]={25,50,75,100};     //Percent of filling given in project

    to_file.open("data.txt", std::fstream::out);    //To clear data
    to_file.close();


    for (int v=0; v<V_NUMBER; v++)      //V_NUMBER of sizes of graph
    {
        max_number_edge[v]=vertices[v]*(vertices[v]-1)/2;   //Find the max amount of possible edges
        for (int f=0; f<4; f++)     //4 different number of fillings of graph
        {
            edges[v][f]=filling[f]*max_number_edge[v]/100;      //Number of edges given by filling percentage
            for (int i=0; i<INSTANCES; i++)       //100 different instances of the same type of graph
                insert_to_file(vertices[v],edges[v][f], to_file);  
        }
    }
}

Graph_Matrix **** all_graphs(unsigned int const& vertices, unsigned int const& number_fill, unsigned int const& instances, ifstream & input)
{
    Graph_Matrix **** Klasa=new Graph_Matrix***[vertices];
    for (int i=0; i<vertices; i++)
    {
        Klasa[i]=new Graph_Matrix**[number_fill];
        for (int j=0; j<number_fill; j++)
        {
            Klasa[i][j]=new Graph_Matrix*[instances];
            for (int k=0; k<instances; k++)
            {
                Klasa[i][j][k]=new Graph_Matrix(input);
            }
        } 
    }
    return Klasa;
}

int main()
{
    srand(time(NULL));

    fstream Data_File;
    ifstream Input;
    generate_data(Data_File);
    Input.open("data.txt", ifstream::in);
    Graph_Matrix **** Klasa=all_graphs(V_NUMBER,4,INSTANCES,Input);
    Input.close();

    Klasa[0][0][0]->show_matrix();
    return 0;
}