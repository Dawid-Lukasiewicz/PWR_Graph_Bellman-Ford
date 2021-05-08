#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<string>

#define MAX 4294967295 
using namespace std;

class Graph_Matrix
{
private:
    unsigned int Vertices_Number, Edge_Number, Starting_Point;
    unsigned int **Matrix;

    unsigned int *Cost=nullptr;
    // int **Path=nullptr;
    int *Path=nullptr;
public:
    Graph_Matrix(unsigned int & vertices, unsigned int & edges, unsigned int & start);
    Graph_Matrix(ifstream& input);  //From file
    ~Graph_Matrix();

    unsigned int & set_Vertices_Number();
    const unsigned int & get_Vertices_Number();
    unsigned int & set_Edge_Number();
    const unsigned int & get_Edge_Number();

    void show_matrix();
    void show_matrix(fstream& output);

    void show_path(unsigned int vertix_number);
    void show_path();
    void show_path(fstream& output);

    void solve_BF();
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
            Matrix[v2][v1]=weight;
            // Matrix[v2][v1]=weight; //
        }
}

Graph_Matrix::~Graph_Matrix()
{
    for (int i=0;i<Vertices_Number; i++)
    {
        delete[] Matrix[i];
        // delete[] Path[i];
    }
    delete Matrix;
    delete Path;
    delete Cost;
}

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

void Graph_Matrix::show_matrix(fstream& output)
{
    for (int i=0; i<Vertices_Number; i++)
    {
        for (int j=0; j<Vertices_Number; j++)
        {
            output<<Matrix[i][j]<<"  ";
        }
        output<<endl;
    }
}

// void Graph_Matrix::show_path(unsigned int vertix_number)
// {
//     cout<<"Starting_Point: "<<Starting_Point<<endl;
//     cout<<"Path to "<<vertix_number<<" vertix: ";

//     for(int i=0; i<Vertices_Number; i++)
//     {
//         if(Path[vertix_number][i]!=MAX && Path[vertix_number][i]!=-1)
//         {
//             cout<<Path[vertix_number][i]<<"  ";
//         }
//     }
//     cout<<endl;

//     cout<<"Final cost: "<<Cost[vertix_number]<<endl;
// }

// void Graph_Matrix::show_path()
// {
//     cout<<"Starting_Point: "<<Starting_Point<<endl;
//     for (int vertix_number=0; vertix_number<Vertices_Number; vertix_number++)
//     {
//         cout<<"Path to "<<vertix_number<<" vertix: ";

//         for(int i=0; i<Vertices_Number; i++)
//         {
//             if(Path[vertix_number][i]!=-1)
//             {
//                 cout<<Path[vertix_number][i]<<"  ";
//             }
//         }
//         cout<<endl;
//         cout<<"Final cost: "<<Cost[vertix_number]<<endl;
//     }
    
// }

void Graph_Matrix::show_path()
{
    cout<<"Starting_Point: "<<Starting_Point<<endl;

    int *display = new int[Vertices_Number];
    int n=0;

    for (int vertix1=0; vertix1<Vertices_Number; vertix1++)
    {
        cout<<"Path to "<<vertix1<<":  ";

        for(int i=vertix1; i!=-1 && n<Vertices_Number; i=Path[i])
            display[n++]=i;
        while(n)
            cout<< display[--n] <<" ";

        
        cout<<endl<<"Final cost: "<<Cost[vertix1]<<endl;
    }
    delete[] display;
}

void Graph_Matrix::show_path(fstream& output)
{
    output<<"Starting_Point: "<<Starting_Point<<endl;

    int *display = new int[Vertices_Number];
    int n=0;

    for (int vertix1=0; vertix1<Vertices_Number; vertix1++)
    {
        output<<"Path to "<<vertix1<<":  ";

        for(int i=vertix1; i!=-1 && n<Vertices_Number; i=Path[i])
            display[n++]=i;
        while(n)
            output<< display[--n] <<" ";

        
        output<<endl<<"Final cost: "<<Cost[vertix1]<<endl;
    }
    delete[] display;
}

void Graph_Matrix::solve_BF()
{
    unsigned int max=4294967295;
    Cost=new unsigned int[Vertices_Number];
    // Path=new int*[Vertices_Number];
    Path=new int[Vertices_Number];

    for (int i=0; i<Vertices_Number; i++)
    {
        Cost[i]=MAX;
        Path[i]=-1;
        // Path[i]=new int[Vertices_Number];
        // for (int j=0; j<Vertices_Number; j++)
        // {
        //     Path[i][j]=-1;
        // }
    }

    Cost[Starting_Point]=0;

    // for(int c = 1; c < Vertices_Number; c++)
    // {
    //     for (int i=0; i<Vertices_Number; i++)
    //     {
    //         for (int j=0; j<Vertices_Number; j++)
    //         {
    //             if(Cost[i] != MAX && Matrix[j][i] != 0 && Cost[j] > Cost[i]+Matrix[j][i])
    //             {
    //                 Cost[j]=Cost[i]+Matrix[j][i];
    //                 Path[j]=i;
    //             }
    //         }
    //     }
    // }

    for(int c = 1; c < Vertices_Number; c++)
    {
        for (int i=0; i<Vertices_Number; i++)
        {
            for (int j=0; j<Vertices_Number; j++)
            {
                if(Cost[j] != MAX && Matrix[i][j] != 0 && Cost[i] > Cost[j]+Matrix[i][j])
                {
                    Cost[i]=Cost[j]+Matrix[i][j];
                    Path[i]=j;
                }
            }
        }
    }
}