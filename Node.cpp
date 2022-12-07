#include "Node.hpp"
#include <iostream>
#include <string>

using namespace std;

Node::Node()
{
    this->data = 0;
    this->nextNode = nullptr;
}

Node::Node(int data)
{
    this->data = data;
    this->nextNode = nullptr;
}

Node *Node::next()
{
    return this->nextNode;
}

void Node::print()
{
    std::cout << "Node: " + std::to_string(this->data) << std::endl;
}