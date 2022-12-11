#include <utility>

namespace ssl
{

    enum ERRORCODE
    {
        VALID = 0,
        INVALID = -1
    };

    class Node
    {
    public:
        int data;

        Node *nextNode;

        Node();

        Node(int data);

        void print();
    };

    class SinglyLinkedList
    {
    private:
        Node *head;
        Node *tail;
        int length;
        void deleteNodes();

    public:
        SinglyLinkedList();

        SinglyLinkedList(SinglyLinkedList &source);

        SinglyLinkedList &operator=(const SinglyLinkedList &source);

        ~SinglyLinkedList();

        SinglyLinkedList *unshift(const int &data);

        SinglyLinkedList *push(const int &data);

        std::pair<ERRORCODE, SinglyLinkedList *> insertAfter(const int &position, const int &data);

        std::pair<ERRORCODE, int> pop();

        std::pair<ERRORCODE, int> shift();

        int size() const;

        int find(const int &data) const;

        std::pair<ERRORCODE, int> get(const int &position);

        std::pair<ERRORCODE, SinglyLinkedList *> replace(const int &position, const int &data);

        std::pair<ERRORCODE, SinglyLinkedList *> deleteNode(const int &position);

        SinglyLinkedList *reverse();

        void print() const;
    };

};
