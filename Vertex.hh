#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<string>
// #include<memory>

using namespace std;

class Vertex
{
    Vertex *Next;
    unsigned int Value, Weight;

public:
    Vertex();
    Vertex(unsigned int & v2, unsigned int & weight, Vertex *list);
    ~Vertex();
    unsigned int & set_value();
    const unsigned int & get_value();
    unsigned int & set_weight();
    const unsigned int & get_weight();
    // Vertex * set_Next();
    void set_Next(Vertex *list);
    Vertex * get_Next() const;
};

// Vertex::Vertex(ifstream& input)
// {
//     input>>Value;
// }

 Vertex::Vertex()
 {}

Vertex::Vertex(unsigned int & v2, unsigned int & weight, Vertex *list):
    Value(v2), Weight(weight), Next(list)
{}

unsigned int & Vertex::set_value()
{
    return Value;
}

const unsigned int & Vertex::get_value()
{
    return Value;
}

unsigned int & Vertex::set_weight()
{
    return Weight;
}

const unsigned int & Vertex::get_weight()
{
    return Weight;
}

void Vertex::set_Next(Vertex *list)
{
    Next=list;
}

Vertex * Vertex::get_Next() const
{
    return Next;
}