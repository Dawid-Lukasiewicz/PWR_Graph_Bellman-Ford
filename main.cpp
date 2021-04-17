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

void generate_to_file(unsigned int vertices, unsigned int edges, fstream & to_file, string & file_name)
{
    
    to_file.open(file_name, std::fstream::app);    //Open file with append mode

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

void generate_parameters(unsigned int *vertices, unsigned int *filling, fstream & to_file, string & file_name)
{
    // unsigned int vertices[V_NUMBER]={10,50,100,500,1000};   //Sizes of graph given in project
    unsigned int max_number_edge[V_NUMBER];     //Max limit of edges possible in given graph
    unsigned int edges[V_NUMBER][4];            //Amount of edges depending od filling od graph
    // unsigned int filling[4]={25,50,75,100};     //Percent of filling given in project

    to_file.open(file_name, std::fstream::out);    //To clear data
    to_file.close();


    for (int v=0; v<V_NUMBER; v++)      //V_NUMBER of sizes of graph
    {
        max_number_edge[v]=vertices[v]*(vertices[v]-1)/2;   //Find the max amount of possible edges
        for (int f=0; f<4; f++)     //4 different number of fillings of graph
        {
            edges[v][f]=filling[f]*max_number_edge[v]/100;      //Number of edges given by filling percentage
            for (int i=0; i<INSTANCES; i++)       //100 different instances of the same type of graph
                generate_to_file(vertices[v],edges[v][f], to_file, file_name);  
        }
    }
}

void insert_parameters(unsigned int vertices_number, unsigned int filling, fstream& file)
{
    file<<"Vertices: "<<vertices_number<<" filling of graph: "<<filling<<"%"<<endl;
}

Graph_Matrix **** load_all_graphs(unsigned int const& vertices, unsigned int const& number_fill, unsigned int const& instances, ifstream & input)
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

Graph_Matrix * create_graph(ifstream& input)
{

    Graph_Matrix *T = new Graph_Matrix(input);

}

void measure_BF(Graph_Matrix & graph_matrix, fstream& output)
{
    clock_t time_start, time_stop;

    time_start=clock();
    graph_matrix.solve_BF();
    time_stop=clock()-time_start;

    output<<(double)(time_stop)/CLOCKS_PER_SEC<<" ";
}



int main()
{
    srand(time(NULL));

    unsigned int vertices[V_NUMBER]={10,50,100,500,1000};
    unsigned int filling[4]={25,50,75,100};

    string Data_Name="data.txt", Measure_Name="measure.txt";
    fstream Data_File, Measure_File;
    ifstream Input;


    generate_parameters(vertices, filling, Data_File, Data_Name);
    Input.open(Data_Name, ifstream::in);

    Measure_File.open(Measure_Name, fstream::out);
    Measure_File.close();
    Measure_File.open(Measure_Name, fstream::app);
    
    for (int i=0; i<V_NUMBER; i++)
    {
        for (int j=0; j<4; j++)
        {
            insert_parameters(vertices[i], filling[j],Measure_File);
            for(int k=0; k<INSTANCES; k++)
            {
                Graph_Matrix T(Input);
                measure_BF(T, Measure_File);
            }
            Measure_File<<endl;
        }
    }
    
    Measure_File.close();
    Input.close();
    
    // Graph_Matrix **** Klasa=load_all_graphs(V_NUMBER,4,INSTANCES,Input);

    // T[0][3][0]->show_matrix();
    // T[0][3][0]->solve_BF();
    // T[0][3][0]->show_path();
    return 0;
}