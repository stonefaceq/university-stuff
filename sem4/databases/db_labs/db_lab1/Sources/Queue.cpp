#include "Queue.h"

bool Queue::isEmpty() const {
    return this->head == nullptr;
}

void Queue::push(long address) {
    if (address < 0) {
        //std::cerr << "Address is out of range.\n";
        return;
    }

    QueueNode* newNode = new QueueNode;
    newNode->address = address;
    if (this->isEmpty()) {
        head = tail = newNode;
    }
    tail->next = newNode;
    tail = newNode;
}
long Queue::pop() {
    if (isEmpty()) {
        return -1;
    }
    QueueNode* temp = this->head;
    long address = temp->address;

    this->head = this->head->next;
    if (this->head == nullptr) {
        this->tail = nullptr;
    }

    delete temp;
    return address;
}