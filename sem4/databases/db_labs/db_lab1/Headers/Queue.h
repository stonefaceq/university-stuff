
#ifndef DB_QUEUE_H
#define DB_QUEUE_H

#include <iostream>

struct QueueNode {
    long address = -1;
    QueueNode* next = nullptr;
};

struct Queue {
    QueueNode* head = nullptr;
    QueueNode* tail = nullptr;

    bool isEmpty() const;

    void push(long address);

    long pop();
};

#endif //DB_QUEUE_H
