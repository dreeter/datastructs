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

    Node *insertAfter(int position, int data);

    int pop();

    int shift();

    int size();

    bool deleteNode(int position);

    Node *reverse();

    void print();
};
