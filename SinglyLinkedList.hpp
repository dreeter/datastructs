#include "Node.hpp"

class SinglyLinkedList
{
private:
    Node *head;
    Node *tail;
    int length;

public:
    SinglyLinkedList();

    Node *unshift(int data);

    Node *push(int data);

    Node *pop();

    Node *shift();

    int size();

    bool deleteNode(int position);

    void print();
};
