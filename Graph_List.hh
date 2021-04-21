#include"Vertex.hh"

using namespace std;

class Graph_List
{

protected:
    unsigned int Vertices_Number;
    unsigned int Edge_Number;
    unsigned int Starting_Number;

    Vertex **Tab_List;

    //After solution
    unsigned int *Cost;
    Vertex **Path;

public:
    Graph_List(unsigned int & vertices, unsigned int & edges, unsigned int & start);
    Graph_List(ifstream & input);
    ~Graph_List();

    void show_list();
    void show_list(unsigned int number);
    void show_list(fstream output);

    void solve_BF();
};

Graph_List::Graph_List(unsigned int & vertices, unsigned int & edges, unsigned int & start):
    Vertices_Number(vertices), Edge_Number(edges), Starting_Number(start)
{}

Graph_List::Graph_List(ifstream & input)
{
    input>>Edge_Number>>Vertices_Number>>Starting_Number;

    // unsigned int tmp[Vertices_Number][3];
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

        cout<<"edge: "<<edge<<endl;
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

Graph_List::~Graph_List() {}

void Graph_List::show_list()
{
    Vertex *list_tmp;
    cout<<"list"<<endl;
    for(int i=0;i<Vertices_Number; i++)
      {
        cout << "tab[" << i << "] =";
        list_tmp = Tab_List[i];
        // int k=0;
        while(list_tmp)
        {
            // k++;
            cout << list_tmp->get_value() <<" ";
            // cout<<"new value ";
            list_tmp = list_tmp->get_Next();
            // cout<<"in new value ";
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

void Graph_List::show_list(fstream output)
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

void Graph_List::solve_BF()
{
    unsigned int max=4294967295;
    // Vertex *list;

    // Path = new Vertex*[Vertices_Number];
    Cost = new unsigned int[Vertices_Number];
    for (int i=0; i<Vertices_Number; i++)
    {
        Path[i]=nullptr;
        Cost[i]=max;
    }
    
    Cost[Starting_Number]=0;

    for(int first=1; first< Vertices_Number; first++)
    {
        for (int i=0; i<Vertices_Number; i++)
        {
            for (list=Tab_List[i]; list; list=list->get_Next())
            {
                if(Cost[i] != max && Cost[list->get_Next()->get_value()] > Cost[i]+list->get_weight())
                {
                    Cost[list->get_Next()->get_value()] = Cost[i] + list->get_weight();
                    // list->set_Next(Path[i]);
                    // Path[i]=list;
                }
            }
        }
    }
}

