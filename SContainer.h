#pragma once

#include <stdexcept> 
#include <string>      
#include <utility>
#include <concepts>

template<typename T>
concept Storable =
    std::is_default_constructible_v<T> &&
    std::is_move_constructible_v<T>;

template <Storable T>
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

    SContainer(const SContainer& other) 
        : head(nullptr), tail(nullptr), size_(0) {
        for (Node* cur = other.head; cur != nullptr; cur = cur->next)
            push_back(cur->value);       
    }

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

    SContainer& operator=(const SContainer& other) {
        if (this == &other) return *this;
        SContainer tmp(other);
        swap(tmp);
        return *this;
    }

    void swap(SContainer& other) noexcept {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size_, other.size_);
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

    std::size_t size() const { 
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
            if (node == nullptr)
                throw std::out_of_range("Итератор разыменование end()");
            return node->value; 
        }
    
        iterator& operator++() { 
            if (node == nullptr)
                throw std::out_of_range("Итератор за пределами списка");
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

    class const_iterator {
        const Node* node;
    public:
        explicit const_iterator(Node* n) : node(n) {}

        const T& operator*() const { 
            if (node == nullptr)
                throw std::out_of_range("const Итератор разыменование end()");
            return node->value; 
        }
    
        const_iterator& operator++() { 
            if (node == nullptr)
                throw std::out_of_range("const Итератор за пределами списка");
            node = node->next; 
            return *this; 
        }

        bool operator!=(const const_iterator& other) { 
            return node != other.node; 
        }
        
        Node* get_node() { 
            return node; 
        }
    };

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }
    
    const_iterator begin() const { return const_iterator(head); }
    const_iterator end()   const { return const_iterator(nullptr); }
};