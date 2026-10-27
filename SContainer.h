#pragma once

#include <cstddef>

template <typename T>
class SContainer {
private:
    struct Node {
        T value;
        Node* previous;
        Node* next;

        Node(T v) : value(v), previous(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t size_ = 0;

public:
    SContainer() = default;

    SContainer(SContainer&& other) noexcept 
        : head(other.head), tail(other.tail), size_(other.size_) 
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }

    ~SContainer() {
        clear();
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size_ = 0;
    }

    SContainer& operator=(SContainer&& other) noexcept {
        if (this == &other) return *this;

        clear();

        head = other.head;
        tail = other.tail;
        size_ = other.size_;

        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;

        return *this;
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
            newNode->previous = tail;
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
            head->previous = newNode;
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
            tail = tail->previous;
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
            head->previous = nullptr;
        }
        delete NodeForDelete;
        --size_;
    }

    void insert(Node* pos, T value) {
        Node* newNode = new Node(value);
        newNode->next = pos;
        newNode->previous = pos->previous;

        if (pos == head) {
            pos->previous = newNode;
            head = newNode;
        } else {
            newNode->previous->next = newNode;
            pos->previous = newNode;
        }
        ++size_;
    }

    void erase(Node* pos) {
        if (pos == head) 
            head = pos->next;
        else 
            pos->previous->next = pos->next;

        if (pos == tail) 
            tail = pos->previous;
        else  
            pos->next->previous = pos->previous;

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