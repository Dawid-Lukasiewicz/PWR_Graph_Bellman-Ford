#include"Vertex.hh"

#define MAX 4294967295

using namespace std;

class Graph_List
{

private:
    unsigned int Vertices_Number;
    unsigned int Edge_Number;
    unsigned int Starting_Point;

    Vertex **Tab_List;

    //After solution
    unsigned int *Cost;
    int *Path;

public:
    Graph_List(unsigned int & vertices, unsigned int & edges, unsigned int & start);
    Graph_List(ifstream & input);
    ~Graph_List();

    void show_list();   //Displaying whole list of neigbourhood to a given file
    void show_list(unsigned int number);    //Displaying list of neigbourhood for pointed vertex
    void show_list(fstream& output);    //Inserting whole list of neigbourhood to a given file

    void show_path();   //Displaying path to every vertex starting from starting point
    void show_path(fstream& output);

    void solve_BF();    //Solving graph with Bellman-Ford algorithm
};

Graph_List::Graph_List(unsigned int & vertices, unsigned int & edges, unsigned int & start):
    Vertices_Number(vertices), Edge_Number(edges), Starting_Point(start)
{}

Graph_List::Graph_List(ifstream& input)
{
    input>>Edge_Number>>Vertices_Number>>Starting_Point;

    unsigned int v1, v2, w;

    Tab_List = new Vertex*[Vertices_Number];
    for (int vert=0;vert<Vertices_Number;vert++)
    {
        Tab_List[vert] = nullptr;
    }

    for (int edge=0;edge<Edge_Number;edge++)
    {
        input>>v1>>v2>>w;
        Vertex *list = new Vertex();

        list->set_value()=v2;
        list->set_weight()=w;
        list->set_Next(Tab_List[v1]);
        Tab_List[v1]=list;
    }

    // for (int edge=0;edge<Edge_Number;edge++) //Loop for undirected graph 
    // {
    //     input>>v1>>v2>>w;
    //     Vertex *list = new Vertex();
        
    //     cout<<"edge: "<<edge<<endl;
    //     list->set_value()=v1;
    //     list->set_weight()=w;
    //     list->set_Next(Tab_List[v2]);
    //     Tab_List[v2]=list;
    // }
    
}

Graph_List::~Graph_List()
{
    for (int i=0; i<Vertices_Number; i++)
    {
        Vertex* current_tmp = Tab_List[i]; // initialize current Vertex to first
        while (current_tmp)
        {
            Vertex* next_tmp = current_tmp->get_Next();    // get next Vertex
            delete current_tmp;                         // delete current Vertex
            current_tmp = next_tmp;                     // set current to "old" next
        }
    }
}

void Graph_List::show_list()
{
    Vertex *list_tmp;
    cout<<"list"<<endl;
    for(int i=0;i<Vertices_Number; i++)
      {
        cout << "tab[" << i << "] =";
        list_tmp = Tab_List[i];
        while(list_tmp)
        {
            cout << list_tmp->get_value() <<" ";
            list_tmp = list_tmp->get_Next();
        }
        cout << endl;
    }
}

void Graph_List::show_list(unsigned int number)
{
    Vertex *list_tmp;
    cout<<"list"<<endl;    
    cout << "tab[" << number << "] =";
    list_tmp = Tab_List[number];
    while(list_tmp)
    {
        cout << list_tmp->get_value() <<" ";
        list_tmp = list_tmp->get_Next();
    }
    cout << endl;

}

void Graph_List::show_list(fstream& output)
{
    Vertex *list_tmp;
    output<<"list\n";
    for(int i=0;i<Vertices_Number; i++)
        {
        output << "tab[" << i << "] =";
        list_tmp = Tab_List[i];
        while(list_tmp)
        {
            output << list_tmp->get_value() <<" ";
            list_tmp = list_tmp->get_Next();
        }
        output << endl;
    }   
}

void Graph_List::show_path()
{
    int *int_tmp=new int[Vertices_Number];
    int counter=0;

    cout<<"Starting_Point: "<<Starting_Point<<endl;
    
    cout<<"Path for list:\n";
    for (int vertix1 = 0; vertix1 < Vertices_Number; vertix1++)
    {
        cout<<"Path to "<<vertix1<<":  ";
        for (int vertix2=vertix1; vertix2!=-1; vertix2=Path[vertix2])
            int_tmp[counter++]=vertix2;
        while (counter)
            cout<<int_tmp[--counter]<<" ";

        cout<<endl;
        cout<<"Final cost: "<<Cost[vertix1]<<endl;
    }
    delete[] int_tmp;
}

void Graph_List::show_path(fstream& output)
{
    int *int_tmp=new int[Vertices_Number];
    int counter=0;

    output<<"Starting_Point "<<Starting_Point<<endl;
    
    output<<"Path for list:\n";
    for (int vertix1 = 0; vertix1 < Vertices_Number; vertix1++)
    {
        output<<"Path to "<<vertix1<<":  ";
        for (int vertix2=vertix1; vertix2!=-1; vertix2=Path[vertix2])
            int_tmp[counter++]=vertix2;
        while (counter)
            output<<int_tmp[--counter]<<" ";

        output<<endl;
        output<<"Final cost: "<<Cost[vertix1]<<endl;
    }
    delete[] int_tmp;
}

void Graph_List::solve_BF()
{
    Vertex *list;

    Path = new int[Vertices_Number];
    Cost = new unsigned int[Vertices_Number];
    for (int i=0; i<Vertices_Number; i++)
    {
        Path[i]=-1;
        Cost[i]=MAX;
    }
    
    Cost[Starting_Point]=0;
    
    for(int first=1; first< Vertices_Number; first++)
    {
        for (int i=0; i<Vertices_Number; i++)
        {
            for (list=Tab_List[i]; list; list=list->get_Next()) //Searching through neighbour list
            {//Cost[list->get_value()] != MAX && Cost[i] > Cost[list->get_value()]+list->get_weight()
                if(Cost[list->get_value()] > Cost[i]+list->get_weight())
                {
                    Cost[list->get_value()] = Cost[i] + list->get_weight();
                    Path[list->get_value()]=i;
                }
            }
        }
    }
}

