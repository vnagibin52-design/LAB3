#pragma once

#include <cstddef>

template <typename T>
class OneWaySContainer {
private:
    struct Node {
        T value;
        Node* next;

        Node(T v) : value(v), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t size_ = 0;

public:
    OneWaySContainer() = default;

    ~OneWaySContainer() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size_ = 0;
    }

    std::size_t size() { 
        return size_; 
    }

    void push_back(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

    void push_front(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size_;
    }

    void pop_back() {
        Node* NodeForDelete = tail;
        if (head == tail) { 
            head = nullptr;
            tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            tail = current;
            tail->next = nullptr;
        }
        delete NodeForDelete;
        --size_;
    }

    void pop_front() {
        Node* NodeForDelete = head;
        if (head == tail) { 
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
        }
        delete NodeForDelete;
        --size_;
    }

    void insert(Node* pos, T value) {
        Node* newNode = new Node(value);
        newNode->next = pos;

        if (pos != head) {
            Node* current = head;
            while (current->next != pos) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size_;
    }

    void erase(Node* pos) {
        if (pos == head) 
            head = pos->next;
        else {
            Node* current = head;
            while (current->next != pos) {
                current = current->next;
            }
            current->next = pos->next;
            if (pos == tail) 
                tail = current;
        }
        delete pos;
        --size_;
    }

    class iterator {
        Node* node;
    public:
        explicit iterator(Node* n) : node(n) {}

        T& operator*() { 
            return node->value; 
        }
    
        iterator& operator++() { 
            node = node->next; 
            return *this; 
        }

        bool operator!=(const iterator& other) { 
            return node != other.node; 
        }
        
        Node* get_node() { 
            return node; 
        }
    };

    iterator begin() { 
        return iterator(head); 
    }

    iterator end() { 
        return iterator(nullptr); 
    }
};