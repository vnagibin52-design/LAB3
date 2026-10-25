#include <iostream>
#include <vector>
#include <list>

template <typename T>
class PContainer {
private:
    T* Data = nullptr;
    std::size_t MaxKE = 0;
    std::size_t KE = 0;

    void expand() {
        std::size_t NewMaxKE;
        if (MaxKE == 0)
            NewMaxKE = 1;
        else 
            NewMaxKE = MaxKE * 2;
        T* NewData = new T[NewMaxKE];
        for (std::size_t i = 0; i < MaxKE; ++i) {
            NewData[i] = std::move(Data[i]);
        }
        delete[] Data;
        Data = NewData;
        MaxKE = NewMaxKE;
    }

public:
    PContainer() = default;

    ~PContainer() { delete[] Data; }

    void push_back(const T& value) {
        if (KE == MaxKE) expand();
        Data[KE] = value;
        ++KE;
    }

    void insert(std::size_t position, const T& value) {

        if (KE == MaxKE) expand();

        for(std::size_t i = KE; i > position; i--){
            Data[i] = std::move(Data[i-1]);
        }
        Data[position] = value;
        ++KE;
    }

    void erase(std::size_t position) {

        for(std::size_t i = position; i < KE-1; i++){
            Data[i] = std::move(Data[i+1]);
        }
        Data[KE - 1].~T();
        --KE;
    }

    T& operator[](std::size_t index) {
        if (index >= KE) throw std::out_of_range("index out of range");
        return Data[index];
    }

    std::size_t size() { return KE; }
    std::size_t capacity() { return MaxKE; }
};

int main() {

    PContainer<int> P;

    for (int i = 0; i < 10; i++){
        P.push_back(i);
    }

    for (int i = 0; i < P.size(); i++){
        std::cout << "Индекс " << i << ": " << P.operator[](i) << "\n";
    }

    std::cout << "Размер контейнера: " << P.size() << "\n";

    std::cout << "Максимальный размер контейнера: " << P.capacity() << "\n";

    P.insert(0, 10);

    P.insert(P.size()/2, 20);

    P.push_back(30);

    for (int i = 0; i < P.size(); i++){
        std::cout << "Индекс " << i << ": " << P.operator[](i) << "\n";
    }

    P.erase(7);
    P.erase(5);
    P.erase(3);
    P.erase(0);

    std::cout << "------------------" << "\n\n";

    for (int i = 0; i < P.size(); i++){
        std::cout << "Индекс " << i << ": " << P.operator[](i) << "\n";
    }


        /*
        std::vector<int> VContainer;

        for (int i = 0; i < 10; i++){
            VContainer.push_back(i);
        }

        for (int i = 0; i < VContainer.size(); i++){
            std::cout << "Индекс " << i << ": " << VContainer.at(i) << "\n";
        }

        std::cout << "Размер контейнера: " << VContainer.size() << "\n";

        VContainer.erase(VContainer.begin() + 6);
        VContainer.erase(VContainer.begin() + 4);
        VContainer.erase(VContainer.begin() + 2);

        for (int i = 0; i < VContainer.size(); i++){
            std::cout << "Индекс " << i << ": " << VContainer.at(i) << "\n";
        }

        VContainer.insert(VContainer.begin(), 10);

        for (int i = 0; i < VContainer.size(); i++){
            std::cout << "Индекс " << i << ": " << VContainer.at(i) << "\n";
        }

        VContainer.insert(VContainer.begin() + VContainer.size()/2, 20);

        for (int i = 0; i < VContainer.size(); i++){
            std::cout << "Индекс " << i << ": " << VContainer.at(i) << "\n";
        }

        VContainer.push_back(30);

        for (int i = 0; i < VContainer.size(); i++){
            std::cout << "Индекс " << i << ": " << VContainer.at(i) << "\n";
        }



        std::cout << "------------------------" << "\n\n\n" << "LIST CONTAINER" << "\n\n";





        std::list<int> LContainer;

        for (int i = 0; i < 10; i++){
            LContainer.push_back(i);
        }

        int i = 0;
        for (int value : LContainer){
            std::cout << "Индекс " << i << ": " << value << "\n";
            i++;
        }

        std::cout << "Размер контейнера: " << LContainer.size() << "\n";

        auto it = LContainer.begin();
        std::advance(it, 2);     
        LContainer.erase(it);  
        std::advance(it, 2);     
        LContainer.erase(it);  
        std::advance(it, 2);     
        LContainer.erase(it);  

        i = 0;
        for (int value : LContainer){
            std::cout << "Индекс " << i << ": " << value << "\n";
            i++;
        }

        LContainer.push_front(10);

        i = 0;
        for (int value : LContainer){
            std::cout << "Индекс " << i << ": " << value << "\n";
            i++;
        }

        it = LContainer.begin();
        std::advance(it, LContainer.size()/2);
        LContainer.insert(it, 20);

        i = 0;
        for (int value : LContainer){
            std::cout << "Индекс " << i << ": " << value << "\n";
            i++;
        }

        LContainer.push_back(30);

        i = 0;
        for (int value : LContainer){
            std::cout << "Индекс " << i << ": " << value << "\n";
            i++;
        }   */
}
