#include"Vertex.hh"

using namespace std;

class Graph_List
{

protected:
    unsigned int Vertices_Number;
    unsigned int Edge_Number;
    unsigned int Starting_Number;

    Vertex **Tab_List;
    unsigned int *Cost;

public:
    Graph_List(unsigned int & vertices, unsigned int & edges, unsigned int & start);
    Graph_List(ifstream & input);
    ~Graph_List();

    void show_list();
    void show_list(unsigned int number);
    void show_list(fstream output);
};

Graph_List::Graph_List(unsigned int & vertices, unsigned int & edges, unsigned int & start):
    Vertices_Number(vertices), Edge_Number(edges), Starting_Number(start)
{}

Graph_List::Graph_List(ifstream & input)
{
    input>>Edge_Number>>Vertices_Number>>Starting_Number;

    unsigned int tmp[Vertices_Number][3];
    Tab_List = new Vertex*[Vertices_Number];

    for (int vert=0;vert<Vertices_Number;vert++)
    {
        Tab_List[vert] = nullptr;
        input>>tmp[vert][0]>>tmp[vert][1]>>tmp[vert][2];

        Vertex *list = new Vertex();
        list->set_value()=tmp[vert][1];
        list->set_weight()=tmp[vert][2];
        list->set_Next(Tab_List[vert]);
        Tab_List[vert]=list;
        // Tab_List[tmp[vert][0]] = new Vertex(tmp[vert][1],tmp[vert][2],Tab_List[tmp[vert][0]]);
    }
    
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