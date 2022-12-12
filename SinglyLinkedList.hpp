#include <utility>
#include <iostream>

namespace ssl
{

    enum ERRORCODE
    {
        VALID = 0,
        INVALID = -1
    };

    template <class T>
    class Node
    {
    public:
        T data;

        Node<T> *nextNode;

        Node() : data(0), nextNode(nullptr) {}

        Node(T data) : data(data), nextNode(nullptr) {}
    };

    template <class T>
    class SinglyLinkedList
    {
    private:
        Node<T> *head;
        Node<T> *tail;
        int length;
        void deleteNodes()
        {
            Node<T> *currentNode = this->head;
            while (currentNode != nullptr)
            {
                Node<T> *nextNode = currentNode->nextNode;
                delete currentNode;
                currentNode = nextNode;
            }
        }

    public:
        SinglyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

        SinglyLinkedList(SinglyLinkedList &source) : head(nullptr), tail(nullptr), length(0)
        {
            if (source.head == nullptr)
                return;

            this->head = new Node<T>(source.head->data);
            Node<T> *targetCurrent = this->head;
            Node<T> *sourceCurrent = source.head;

            while (sourceCurrent->nextNode != nullptr)
            {
                targetCurrent->nextNode = new Node<T>(sourceCurrent->nextNode->data);
                sourceCurrent = sourceCurrent->nextNode;
                targetCurrent = targetCurrent->nextNode;
            }

            this->tail = targetCurrent;
            this->length = source.size();

            return;
        }

        SinglyLinkedList &operator=(const SinglyLinkedList &source)
        {
            deleteNodes();

            this->head = nullptr;
            this->tail = nullptr;
            this->length = 0;

            Node<T> *currentSourceNode = source.head;
            Node<T> *currentTargetNode = this->head;

            if (currentSourceNode == nullptr)
            {
                return *this;
            }

            currentTargetNode = new Node<T>(currentSourceNode->data);
            this->head = currentTargetNode;

            while (currentSourceNode->nextNode != nullptr)
            {
                currentTargetNode->nextNode = new Node<T>(currentSourceNode->nextNode->data);
                currentSourceNode = currentSourceNode->nextNode;
                currentTargetNode = currentTargetNode->nextNode;
            }

            this->tail = currentTargetNode;
            this->length = source.length;

            return *this;
        }

        ~SinglyLinkedList()
        {
            deleteNodes();
        }

        SinglyLinkedList *unshift(const T &data)
        {

            if (this->size() == 0)
            {
                this->push(data);
            }
            else
            {
                Node<T> *new_node;
                try
                {
                    new_node = new Node<T>(data);

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

        SinglyLinkedList *push(const T &data)
        {

            Node<T> *new_node;
            try
            {
                new_node = new Node<T>(data);

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

        std::pair<ERRORCODE, T> pop()
        {
            // Validate pop() is valid or return INVALID
            if (this->size() == 0)
            {
                return std::make_pair(ERRORCODE::INVALID, T());
            }

            // Return data will be the tail
            T poppedNodeData = this->tail->data;
            Node<T> *poppedNode = this->tail;

            // Handle changes to head and tail
            if (this->size() == 1)
            {
                this->head = nullptr;
                this->tail = nullptr;
            }
            else
            {
                Node<T> *currentNode = this->head;
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

        std::pair<ERRORCODE, T> shift()
        {
            // Validate shift() is valid or return NULL
            if (this->size() == 0)
            {
                return std::make_pair(ERRORCODE::INVALID, T());
            }

            // Return data will be the head
            Node<T> *shiftedNode = this->head;
            T shiftedNodeData = this->head->data;

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

        std::pair<ERRORCODE, SinglyLinkedList *> insertAfter(const int &position, const T &data)
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
            Node<T> *currentNode = this->head;
            while (currentPosition < position)
            {
                currentPosition++;
                currentNode = currentNode->nextNode;
            }

            try
            {
                Node<T> *new_node = new Node<T>(data);
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

        std::pair<ERRORCODE, SinglyLinkedList *> deleteNode(const int &position)
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
            Node<T> *previousNode = nullptr;
            int currentPosition = 0;
            Node<T> *currentNode = this->head;
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

        SinglyLinkedList *reverse()
        {
            if (this->size() == 1)
                return this;

            Node<T> *previous = nullptr;
            Node<T> *currentNode = head;
            Node<T> *nextNode = nullptr;

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

        int find(const T &data) const
        {
            if (this->size() == 0)
            {
                return -1;
            }

            bool found = false;

            Node<T> *currentNode = this->head;
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

        std::pair<ERRORCODE, SinglyLinkedList *> replace(const int &position, const T &data)
        {
            if (position < 0 || position >= this->size())
            {
                return std::make_pair(ERRORCODE::INVALID, this);
            }

            Node<T> *currentNode = this->head;
            int currentIndex = 0;
            while (currentIndex < position)
            {
                currentIndex++;
                currentNode = currentNode->nextNode;
            }

            currentNode->data = data;

            return std::make_pair(ERRORCODE::VALID, this);
        }

        std::pair<ERRORCODE, T> extract(const int &position)
        {
            if (position < 0 || position >= this->size())
            {
                return std::make_pair(ERRORCODE::INVALID, -1);
            }

            if (position == 0)
                return this->shift();

            if (position == this->size() - 1)
                return this->pop();

            Node<T> *currentNode = this->head;
            int currentIndex = 0;
            while (currentIndex < position - 1)
            {
                currentIndex++;
                currentNode = currentNode->nextNode;
            }

            T return_data = currentNode->nextNode->data;
            Node<T> *node_to_delete = currentNode->nextNode;
            currentNode->nextNode = currentNode->nextNode->nextNode;
            delete node_to_delete;
            this->length--;

            return std::make_pair(ERRORCODE::VALID, return_data);
        }

        int size() const
        {
            return this->length;
        }

        friend std::ostream &operator<<(std::ostream &out_stream, const SinglyLinkedList &list)
        {
            if (list.head == nullptr)
            {
                out_stream << "Empty List";
                return out_stream;
            }

            out_stream << "Head: " << list.head->data << std::endl;
            out_stream << "Tail: " << list.tail->data << std::endl;
            out_stream << "Length: " << list.length << std::endl;

            Node<T> *currentNode = list.head;
            int currentNodeIndex = 0;
            while (currentNode != nullptr)
            {
                out_stream << "Node " << currentNodeIndex << ": " << currentNode->data << " -> ";
                currentNode = currentNode->nextNode;
                currentNodeIndex++;
            }

            out_stream << "nullptr" << std::endl;

            return out_stream;
        }

        bool operator==(SinglyLinkedList &other)
        {
            if (this->size() != other.size())
            {
                return false;
            }

            Node<T> *otherCurrentNode = other.head;
            Node<T> *thisCurrentNode = this->head;

            while (otherCurrentNode != nullptr)
            {
                if (otherCurrentNode->data != thisCurrentNode->data)
                {
                    return false;
                }
                otherCurrentNode = otherCurrentNode->nextNode;
                thisCurrentNode = thisCurrentNode->nextNode;
            }

            return true;
        }

        bool operator!=(SinglyLinkedList &other)
        {
            return !(*this == other);
        }
    };

};
