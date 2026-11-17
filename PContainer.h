#pragma once

#include <stdexcept> 
#include <string>      
#include <utility>
#include "Storable.h"

template <Storable T>
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

    PContainer(const PContainer& other)
        : Data(nullptr), size_(other.size_), Maxsize_(other.Maxsize_) 
    {
        if (Maxsize_ > 0){
            Data = new T[Maxsize_];
            for(std::size_t i = 0; i < size_; i++){
                Data[i] = other.Data[i];
            }
        }
    }

    PContainer(PContainer&& other) noexcept 
        : Data(other.Data), size_(other.size_), Maxsize_(other.Maxsize_) 
    {
        other.Data = nullptr;
        other.size_ = 0;
        other.Maxsize_ = 0;
    }

    PContainer& operator=(const PContainer& other){
        if (this == &other) return *this;

        delete[] Data;
        size_ = other.size_;
        Maxsize_ = other.Maxsize_;

        if (Maxsize_ > 0){
            Data = new T[Maxsize_];
            for (size_t i = 0; i < size_; i++)
            Data[i] = other.Data[i];
        } else {
            Data = nullptr;
        }

        return *this;
    }

    PContainer& operator=(PContainer&& other) noexcept {
        if (this == &other) return *this;

        Data = other.Data;
        size_ = other.size_;
        Maxsize_ = other.Maxsize_;
        
        other.Data = nullptr;
        other.size_ = 0;
        other.Maxsize_ = 0;

        return *this;
    }

    void push_back(const T& value) {
        if (size_ == Maxsize_) expand();
        Data[size_] = value;
        ++size_;
    }

    void insert(std::size_t position, const T& value) {

        if (position > size_) {
        throw std::out_of_range(
            "PContainer::insert: index " + std::to_string(position) +
            ", допустимо [0, " + std::to_string(size_) + "]");
        }

        if (size_ == Maxsize_) expand();

        for(std::size_t i = size_; i > position; i--){
            Data[i] = std::move(Data[i-1]);
        }
        Data[position] = value;
        ++size_;
    }

    void erase(std::size_t position) {

        if (position >= size_) {
        throw std::out_of_range(
            "PContainer::erase: index " + std::to_string(position) +
            ", допустимо [0, " + std::to_string(size_) + "]");
        }

        for(std::size_t i = position; i < size_-1; i++){
            Data[i] = std::move(Data[i+1]);
        }
        Data[size_ - 1] = T();
        --size_;
    }

    T& operator[](std::size_t index) {
        return Data[index];
    }

    const T& operator[](std::size_t index) const { 
        return Data[index]; 
    }	

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return Maxsize_; }
};