
#ifndef DB_NODE_H
#define DB_NODE_H

#include <iostream>

struct ListNode {
    int id = -1;
    long address = -1;
    ListNode* next = nullptr;
};


long getAddress(int id, ListNode* head);

bool isIdFree(int id, ListNode* head);

void addListNode(int id, long address, ListNode** head);
void deleteListNode(int id, ListNode** head);

void sortList(ListNode** head);

int getSize(ListNode* head);

void printList(ListNode* head);

#endif //DB_NODE_H
