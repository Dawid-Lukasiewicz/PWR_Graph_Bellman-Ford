#include<cstdlib>
#include<iostream>
#include<algorithm>

class Vertex
{
    Vertex *Neighbours=nullptr;
    unsigned int Value, Weight;

public:
    Vertex();
    Vertex(unsigned int & value,unsigned int & weight, Vertex * neigbours):
        Value(value), Weight(weight), Neighbours(neigbours) {}
    ~Vertex();
    unsigned int & set_value();
    const unsigned int & get_value();
    unsigned int & set_weight();
    const unsigned int & get_weight();
    Vertex * set_Neigbours();
};

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