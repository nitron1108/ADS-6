// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_


template<typename T>
class TPQueue {
private:
    struct Element {
        T value;
        Element* nextElement;
        explicit Element(const T& val) : value(val), nextElement(nullptr) {}
    };

    Element* front;
    Element* back;

public:
    TPQueue() : front(nullptr), back(nullptr) {}

    ~TPQueue() {
        while (front) {
            Element* temp = front;
            front = front->nextElement;
            delete temp;
        }
    }

    void enqueue(const T& item) {
        Element* node = new Element(item);

        if (!front || item.prior > front->value.prior) {
            node->nextElement = front;
            front = node;
            if (!back) back = front;
            return;
        }

        Element* current = front;
        while (current->nextElement && current->nextElement->value.prior >= item.prior) {
            current = current->nextElement;
        }

        node->nextElement = current->nextElement;
        current->nextElement = node;

        if (!node->nextElement) {
            back = node;
        }
    }

    T dequeue() {
        if (!front) {
            throw std::runtime_error("Очередь пуста!");
        }

        Element* temp = front;
        T out = front->value;
        front = front->nextElement;
        if (!front) back = nullptr;
        delete temp;
        return out;
    }

    bool empty() const {
        return front == nullptr;
    }
};

struct SYM {
    char ch;
    int prior;
};
