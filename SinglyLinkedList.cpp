#include "SinglyLinkedList.hpp"
#include <iostream>

SinglyLinkedList::SinglyLinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

Node *SinglyLinkedList::unshift(int data)
{

    if (this->head == nullptr)
    {
        this->push(data);
    }
    else
    {
        Node *new_node;
        try
        {
            new_node = new Node(data);

            new_node->nextNode = this->head;
            this->head = new_node;

            this->length++;
        }
        catch (std::bad_alloc &e)
        {
            std::cout << "Unshift memory allocation failed" << e.what() << std::endl;
        }
    }

    return this->head;
}

Node *SinglyLinkedList::push(int data)
{
    Node *new_node;
    try
    {
        new_node = new Node(data);

        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            this->tail->nextNode = new_node;
            this->tail = new_node;
        }

        this->length++;
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "Push memory allocation failed" << e.what() << std::endl;
    }

    return this->head;
}

Node *SinglyLinkedList::pop()
{
    Node *poppedNode = this->tail;

    if (this->head == nullptr)
    {
        return poppedNode;
    }

    if (this->length == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->length--;
        return poppedNode;
    }

    Node *currentNode = this->head;
    while (currentNode->nextNode != nullptr)
    {
        if (currentNode->nextNode->nextNode == nullptr)
        {
            this->tail = currentNode;
            this->tail->nextNode = nullptr;
            break;
        }
        else
        {
            currentNode = currentNode->nextNode;
        }
    }

    this->length--;

    return poppedNode;
}

Node *SinglyLinkedList::shift()
{
    Node *shiftedNode = this->head;

    if (this->head == nullptr)
    {
        return shiftedNode;
    }

    if (this->length == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->length--;
        return shiftedNode;
    }

    this->head = this->head->nextNode;
    this->length--;

    return shiftedNode;
}

bool SinglyLinkedList::deleteNode(int position)
{
    return false;
}

int SinglyLinkedList::size()
{
    return this->length;
}

void SinglyLinkedList::print()
{
    std::cout << "Head is: ";
    this->head->print();
    std::cout << "Tail is: ";
    this->tail->print();
    std::cout << "Length is: ";
    std::cout << this->size() << std::endl;

    Node *currentNode = this->head;
    while (currentNode != nullptr)
    {
        currentNode->print();
        currentNode = currentNode->nextNode;
    }
}