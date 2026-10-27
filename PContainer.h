#pragma once

#include <cstddef>
#include <utility>

template <typename T>
class PContainer {
private:
    T* Data = nullptr;
    std::size_t Maxsize_ = 0;
    std::size_t size_ = 0;

    void expand() {
        std::size_t NewMaxsize_;
        if (Maxsize_ == 0)
            NewMaxsize_ = 1;
        else 
            NewMaxsize_ = Maxsize_ * 2;
        T* NewData = new T[NewMaxsize_];
        for (std::size_t i = 0; i < Maxsize_; ++i) {
            NewData[i] = std::move(Data[i]);
        }
        delete[] Data;
        Data = NewData;
        Maxsize_ = NewMaxsize_;
    }

public:
    PContainer() = default;

    ~PContainer() { delete[] Data; }

    void push_back(const T& value) {
        if (size_ == Maxsize_) expand();
        Data[size_] = value;
        ++size_;
    }

    void insert(std::size_t position, const T& value) {

        if (size_ == Maxsize_) expand();

        for(std::size_t i = size_; i > position; i--){
            Data[i] = std::move(Data[i-1]);
        }
        Data[position] = value;
        ++size_;
    }

    void erase(std::size_t position) {

        for(std::size_t i = position; i < size_-1; i++){
            Data[i] = std::move(Data[i+1]);
        }
        Data[size_ - 1].~T();
        --size_;
    }

    T& operator[](std::size_t index) {
        return Data[index];
    }

    std::size_t size() { return size_; }
    std::size_t capacity() { return Maxsize_; }
};