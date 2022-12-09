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

    if (this->size() == 0)
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

        if (this->size() == 0)
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

int SinglyLinkedList::pop()
{
    // Validate pop() is valid or return NULL
    if (this->size() == 0)
    {
        return NULL;
    }

    // Return data will be the tail
    int poppedNodeData = this->tail->data;
    Node *poppedNode = this->tail;

    // Handle changes to head and tail
    if (this->size() == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
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
    }
    this->length--;
    delete poppedNode;

    return poppedNodeData;
}

int SinglyLinkedList::shift()
{
    // Validate shift() is valid or return NULL
    if (this->size() == 0)
    {
        return NULL;
    }

    // Return data will be the head
    Node *shiftedNode = this->head;
    int shiftedNodeData = this->head->data;

    // Update new head
    if (this->size() == 1)
    {
        return this->pop();
    }
    else
    {
        this->head = this->head->nextNode;
        this->length--;
        delete shiftedNode;
    }

    return shiftedNodeData;
}

Node *SinglyLinkedList::insertAfter(int position, int data)
{

    // Verify the position to insert at is valid given the list size
    if (position < 0 || position > this->size())
    {
        return nullptr;
    }

    // If we're inserting at the end or beginning, call unshift or push, respectively
    if (position == this->size() - 1)
    {
        return this->push(data);
    }

    // Traverse until we've reach the position, insert
    int currentPosition = 0;
    Node *currentNode = this->head;
    while (currentPosition < position)
    {
        currentPosition++;
        currentNode = currentNode->nextNode;
    }

    try
    {
        Node *new_node = new Node(data);
        new_node->nextNode = currentNode->nextNode;
        currentNode->nextNode = new_node;
        this->length++;
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "InsertAfter memory allocation failed" << e.what() << std::endl;
        return nullptr;
    }

    return this->head;
}

bool SinglyLinkedList::deleteNode(int position)
{
    // Validate the position is valid given the list
    if (position < 0 || position >= this->size())
    {
        return false;
    }

    // Simply pop or shift from the list if the first or last node is being deleted
    if (position == 0)
    {
        return (this->shift() != NULL);
    }
    if (position == this->size() - 1)
    {
        return (this->pop() != NULL);
    }

    // Loop until we've reached the node to delete, linking the previousNode and nextNode
    Node *previousNode = nullptr;
    int currentPosition = 0;
    Node *currentNode = this->head;
    while (currentPosition < position)
    {
        currentPosition++;
        previousNode = currentNode;
        currentNode = currentNode->nextNode;
    }

    previousNode->nextNode = currentNode->nextNode;
    delete currentNode;
    this->length--;

    return true;
}

Node *SinglyLinkedList::reverse()
{
    if (this->size() == 1)
        return this->head;

    Node *previous = nullptr;
    Node *currentNode = head;
    Node *nextNode = nullptr;

    this->tail = currentNode;
    while (currentNode->nextNode != nullptr)
    {
        nextNode = currentNode->nextNode;
        currentNode->nextNode = previous;
        previous = currentNode;
        currentNode = nextNode;
    }
    currentNode->nextNode = previous;
    this->head = currentNode;

    return this->head;
}

int SinglyLinkedList::size()
{
    return this->length;
}

void SinglyLinkedList::print()
{
    if (this->head == nullptr)
    {
        std::cout << "List is empty" << std::endl;
        return;
    }

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