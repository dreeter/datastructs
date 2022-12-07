#include <string>
#include <iostream>
#include "SinglyLinkedList.hpp"

using namespace std;

int main()
{
    SinglyLinkedList my_list;

    my_list.push(10);
    my_list.push(20);
    my_list.push(30);
    my_list.push(40);
    my_list.push(50);
    my_list.insertAfter(0, 33);
    my_list.insertAfter(5, 77);

    my_list.print();
}