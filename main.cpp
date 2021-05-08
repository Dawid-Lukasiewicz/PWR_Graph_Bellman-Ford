#include<cstdlib>
#include<iostream>
#include"Graph_Matrix.hh"
#include"Graph_List.hh"

#define V_NUMBER 5
#define INSTANCES 100
#define F_NUMBER 4

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
    unsigned int edges[V_NUMBER][F_NUMBER];            //Amount of edges depending od filling od graph
    // unsigned int filling[4]={25,50,75,100};     //Percent of filling given in project

    to_file.open(file_name, std::fstream::out);    //To clear data
    to_file.close();


    for (int v=0; v<V_NUMBER; v++)      //V_NUMBER of sizes of graph
    {
        max_number_edge[v]=vertices[v]*(vertices[v]-1)/2;   //Find the max amount of possible edges
        for (int f=0; f<F_NUMBER; f++)     //4 different number of fillings of graph
        {
            edges[v][f]=filling[f]*max_number_edge[v]/100;      //Number of edges given by filling percentage
            for (int i=0; i<INSTANCES; i++)       //100 different instances of the same type of graph
            {
                generate_to_file(vertices[v],edges[v][f], to_file, file_name);  
            }
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

void measure_BF(Graph_Matrix & graph_matrix, fstream& output)
{
    clock_t time_start, time_stop;

    time_start=clock();
    graph_matrix.solve_BF();
    time_stop=clock()-time_start;

    output<<" "<<(float)(time_stop)/CLOCKS_PER_SEC<<" ";
}

void measure_BF(Graph_List & graph_list, fstream& output)
{
    clock_t time_start, time_stop;

    time_start=clock();
    graph_list.solve_BF();
    time_stop=clock()-time_start;
    // cout<<(double)(time_stop)/CLOCKS_PER_SEC<<" ";
    output<<" "<<(float)(time_stop)/CLOCKS_PER_SEC<<" ";
}

void measure_list_graph(unsigned int * vertices, unsigned int * filling, ifstream& Input, string& Data_Name, string& Measure_Name)
{    
    fstream Measure_File;

    Measure_File.open(Measure_Name, fstream::out);
    Measure_File.close();                           //To clean file before opening it with append mode

    Measure_File.open(Measure_Name, fstream::app);
    Measure_File.precision(6);
    
    Input.open(Data_Name, ifstream::in); //Opening file containing data to create graph

    for (int i=0; i<V_NUMBER; i++)
    {
        for (int j=0; j<F_NUMBER; j++)
        {
            insert_parameters(vertices[i], filling[j],Measure_File);
            for(int k=0; k<INSTANCES; k++)
            {
                Graph_List lista(Input);
                measure_BF(lista, Measure_File);
            }
            Measure_File<<endl;
        }
    }
    Input.close();
    Measure_File.close();
}

void measure_matrix_graph(unsigned int * vertices, unsigned int * filling, ifstream& Input, string& Data_Name, string& Measure_Name)
{
    fstream Measure_File;

    Measure_File.open(Measure_Name, fstream::out);
    Measure_File.close();                           //To clean file before opening it with append mode

    Measure_File.open(Measure_Name, fstream::app);
    Measure_File.precision(6);

    Input.open(Data_Name, ifstream::in); //Opening file containing data to create graph

    for (int i=0; i<V_NUMBER; i++)
    {
        for (int j=0; j<F_NUMBER; j++)
        {
            insert_parameters(vertices[i], filling[j],Measure_File);
            for(int k=0; k<INSTANCES; k++)
            {
                Graph_Matrix macierz(Input);
                measure_BF(macierz, Measure_File);
            }
            Measure_File<<endl;
        }
    }
    Input.close();
    Measure_File.close();
}

void measurement()
{
    srand(time(NULL));
    // unsigned int vertices[V_NUMBER]={10};
    // unsigned int filling[F_NUMBER]={100};
    unsigned int vertices[V_NUMBER]={10,50,100,500,1000};
    unsigned int filling[F_NUMBER]={25,50,75,100};

    string Data_Name="data.txt";
    string Measure_Name_Matrix="measure_matrix.txt";
    string Measure_Name_List="measure_list.txt";
    fstream Data_File, Measure_File;
    ifstream Input;


    generate_parameters(vertices, filling, Data_File, Data_Name);
    

    //To clean file before opening it with append mode
    Measure_File.open(Measure_Name_Matrix, fstream::out);
    Measure_File.close();    

    Measure_File.open(Measure_Name_List, fstream::out);
    Measure_File.close();
    //Opening files in append mode
    Measure_File.open(Measure_Name_Matrix, fstream::app);
    
    Input.open(Data_Name, ifstream::in); //Opening file containing data to create graph
    for (int i=0; i<V_NUMBER; i++)
    {
        for (int j=0; j<F_NUMBER; j++)
        {
            insert_parameters(vertices[i], filling[j],Measure_File);
            for(int k=0; k<INSTANCES; k++)
            {
                Graph_Matrix macierz(Input);
                measure_BF(macierz, Measure_File);
            }
            Measure_File<<endl;
        }
    }
    Input.close();
    Measure_File.close();
    

    Measure_File.open(Measure_Name_List, fstream::app);
    Input.open(Data_Name, ifstream::in); //Opening file containing data to create graph
    for (int i=0; i<V_NUMBER; i++)
    {
        for (int j=0; j<F_NUMBER; j++)
        {
            insert_parameters(vertices[i], filling[j],Measure_File);
            for(int k=0; k<INSTANCES; k++)
            {
                Graph_List lista(Input);
                measure_BF(lista, Measure_File);
            }
            Measure_File<<endl;
        }
    }
    Measure_File.close();
    Input.close();
}


int main()
{
    srand(time(NULL));

    //Declaring variables for small measuremnt

    ifstream small_file;
    fstream result_file;
    string data="single_data.txt";
    string list="list_results.txt";
    string matrix="matrix_results.txt";

    //Declaring variables for big measurement

    unsigned int vertices[V_NUMBER]={10,50,100,500,1000};
    unsigned int filling[F_NUMBER]={25,50,75,100};
    // unsigned int vertices[V_NUMBER]={10};
    // unsigned int filling[F_NUMBER]={25};


    fstream Data_File;
    string Data_Name="wyniki_pomiarow/data.txt";

    ifstream Input;
    string Measure_Name_List="measure_list.txt";
    string Measure_Name_Matrix="measure_matrix.txt";

    

    char type;
    do
    {
        cout<<"Program used to test efficiency of Bellman-Ford algorithm in parameter of size of a graph and it's filling percentage."<<endl;
        cout<<"Type:"<<endl;
        cout<<"g - generate data"<<endl;
        // cout<<"m - measure matrix graph"<<endl;
        // cout<<"l - measure list graph"<<endl;
        cout<<"a - measure list and matrix graph (takes about 60 minutes)"<<endl;
        cout<<"d - measure and display results of a 10 size graph with 100% filling"<<endl;
        cout<<"q - exit"<<endl;
        
        cin>>type;
        switch (type)
        {
        case 'g':
            cout<<"Zablokowane"<<endl;
            //generate_parameters(vertices, filling, Data_File, Data_Name);
            break;

        case 'a':
            measure_matrix_graph(vertices, filling, Input, Data_Name, Measure_Name_Matrix);
            measure_list_graph(vertices, filling, Input, Data_Name, Measure_Name_List);
            break;

        case 'd':
            {
            small_file.open(data, fstream::in);
            Graph_Matrix macierz(small_file);
            small_file.close();

            macierz.solve_BF();

            result_file.open(matrix, fstream::out);
            result_file.close();
            result_file.open(matrix, fstream::app);

            macierz.show_matrix(result_file);
            macierz.show_path(result_file);
            result_file.close();
            }
            {
            small_file.open(data, fstream::in);
            Graph_List lista(small_file);
            small_file.close();

            lista.solve_BF();

            result_file.open(list, fstream::out);
            result_file.close();
            result_file.open(list, fstream::app);

            lista.show_list(result_file);
            lista.show_path(result_file);
            result_file.close();
            }
            break;
        case 'q':
            return 0;
            break;

        default:
            break;
        }
    }while (type!='q');
    return 0;
}