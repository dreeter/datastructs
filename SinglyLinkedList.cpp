#include "SinglyLinkedList.hpp"
#include <iostream>

namespace ssl
{
    Node::Node() : data(0), nextNode(nullptr) {}

    Node::Node(int data) : data(data), nextNode(nullptr) {}

    void Node::print()
    {
        std::cout << "Node: " + std::to_string(this->data) << std::endl;
    }

    SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    SinglyLinkedList::SinglyLinkedList(SinglyLinkedList &source) : head(nullptr), tail(nullptr), length(0)
    {
        std::cout << "Copy constructor being called" << std::endl;
        if (source.head == nullptr)
            return;

        this->head = new Node(source.head->data);
        Node *targetCurrent = this->head;
        Node *sourceCurrent = source.head;

        while (sourceCurrent->nextNode != nullptr)
        {
            targetCurrent->nextNode = new Node(sourceCurrent->nextNode->data);
            sourceCurrent = sourceCurrent->nextNode;
            targetCurrent = targetCurrent->nextNode;
        }

        this->tail = targetCurrent;
        this->length = source.size();

        return;
    }

    SinglyLinkedList &SinglyLinkedList::operator=(const SinglyLinkedList &source)
    {
        deleteNodes();

        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;

        Node *currentSourceNode = source.head;
        Node *currentTargetNode = this->head;

        if (currentSourceNode == nullptr)
        {
            return *this;
        }

        currentTargetNode = new Node(currentSourceNode->data);
        this->head = currentTargetNode;

        while (currentSourceNode->nextNode != nullptr)
        {
            currentTargetNode->nextNode = new Node(currentSourceNode->nextNode->data);
            currentSourceNode = currentSourceNode->nextNode;
            currentTargetNode = currentTargetNode->nextNode;
        }

        this->tail = currentTargetNode;
        this->length = source.length;

        return *this;
    }

    SinglyLinkedList::~SinglyLinkedList()
    {
        deleteNodes();
    }

    void SinglyLinkedList::deleteNodes()
    {
        Node *currentNode = this->head;
        while (currentNode != nullptr)
        {
            Node *nextNode = currentNode->nextNode;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    SinglyLinkedList *SinglyLinkedList::unshift(const int &data)
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
                throw;
            }
        }

        return this;
    }

    SinglyLinkedList *SinglyLinkedList::push(const int &data)
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
            throw;
        }

        return this;
    }

    std::pair<ERRORCODE, int> SinglyLinkedList::pop()
    {
        // Validate pop() is valid or return INVALID
        if (this->size() == 0)
        {
            return std::make_pair(ERRORCODE::INVALID, 0);
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

        return std::make_pair(ERRORCODE::VALID, poppedNodeData);
    }

    std::pair<ERRORCODE, int> SinglyLinkedList::shift()
    {
        // Validate shift() is valid or return NULL
        if (this->size() == 0)
        {
            return std::make_pair(ERRORCODE::INVALID, 0);
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

        return std::make_pair(ERRORCODE::VALID, shiftedNodeData);
    }

    std::pair<ERRORCODE, SinglyLinkedList *> SinglyLinkedList::insertAfter(const int &position, const int &data)
    {

        // Verify the position to insert at is valid given the list size
        if (position < 0 || position > this->size())
        {
            return std::make_pair(ERRORCODE::INVALID, nullptr);
        }

        // If we're inserting at the end just push
        if (position == this->size() - 1)
        {
            return std::make_pair(ERRORCODE::VALID, this->push(data));
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
            throw;
        }

        return std::make_pair(ERRORCODE::VALID, this);
    }

    std::pair<ERRORCODE, SinglyLinkedList *> SinglyLinkedList::deleteNode(const int &position)
    {
        // Validate the position is valid given the list
        if (position < 0 || position >= this->size())
        {
            return std::make_pair(ERRORCODE::INVALID, nullptr);
        }

        // Simply pop or shift from the list if the first or last node is being deleted
        if (position == 0)
        {
            if (this->shift().first == ERRORCODE::VALID)
                return std::make_pair(ERRORCODE::VALID, this);
        }
        if (position == this->size() - 1)
        {
            if (this->pop().first == ERRORCODE::VALID)
                return std::make_pair(ERRORCODE::VALID, this);
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

        return std::make_pair(ERRORCODE::VALID, this);
    }

    SinglyLinkedList *SinglyLinkedList::reverse()
    {
        if (this->size() == 1)
            return this;

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

        return this;
    }

    int SinglyLinkedList::find(const int &data) const
    {
        if (this->size() == 0)
        {
            return -1;
        }

        bool found = false;

        Node *currentNode = this->head;
        int currentIndex = 0;
        while (currentNode != nullptr)
        {
            if (currentNode->data == data)
            {
                found = true;
                break;
            }
            else
            {
                currentIndex++;
                currentNode = currentNode->nextNode;
            }
        }

        if (found)
        {
            return currentIndex;
        }
        else
        {
            return -1;
        }
    }

    std::pair<ERRORCODE, SinglyLinkedList *> SinglyLinkedList::replace(const int &position, const int &data)
    {
        if (position < 0 || position >= this->size())
        {
            return std::make_pair(ERRORCODE::INVALID, this);
        }

        Node *currentNode = this->head;
        int currentIndex = 0;
        while (currentIndex < position)
        {
            currentIndex++;
            currentNode = currentNode->nextNode;
        }

        currentNode->data = data;

        return std::make_pair(ERRORCODE::VALID, this);
    }

    std::pair<ERRORCODE, int> SinglyLinkedList::get(const int &position)
    {
        if (position < 0 || position >= this->size())
        {
            return std::make_pair(ERRORCODE::INVALID, -1);
        }

        if (position == 0)
            return this->shift();

        if (position == this->size() - 1)
            return this->pop();

        Node *currentNode = this->head;
        int currentIndex = 0;
        while (currentIndex < position - 1)
        {
            currentIndex++;
            currentNode = currentNode->nextNode;
        }

        int return_data = currentNode->nextNode->data;
        Node *node_to_delete = currentNode->nextNode;
        currentNode->nextNode = currentNode->nextNode->nextNode;
        delete node_to_delete;
        this->length--;

        return std::make_pair(ERRORCODE::VALID, return_data);
    }

    int SinglyLinkedList::size() const
    {
        return this->length;
    }

    void SinglyLinkedList::print() const
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
};
