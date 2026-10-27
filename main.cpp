#include "SContainer.h"
#include "PContainer.h"
#include "OneWaySContainer.h"
#include <iostream>
#include <stdexcept> 

int main() {

    OneWaySContainer<int> S;

    for (int i = 0; i < 10; i++){
        S.push_back(i);
    }

    int i = 0;
    for (int value : S){
        std::cout << value << "\n";
    }

    std::cout << "Размер контейнера: " << S.size() << "\n";

    auto it = S.begin();
    ++it;
    ++it;
    S.erase(it.get_node()); 

    ++it;
    ++it;    
    S.erase(it.get_node()); 

    ++it;
    ++it;     
    S.erase(it.get_node());

    for (int value : S){
        std::cout << value << "\n";
    }

    S.push_front(10);

    for (int value : S){
        std::cout << value << "\n";
    }

    it = S.begin();
    for(int i = 0; i < S.size()/2; i++){
        ++it;
    }
    S.insert(it.get_node(), 20);

    for (int value : S){
        std::cout << value << "\n";
    }

    S.push_back(30);

    for (int value : S){
        std::cout << value << "\n";
    }

    std::cout << "---------------------\n";
    std::cout << "---------------------\n";
    std::cout << "---------------------\n";

    /*
    PContainer<int> P;

    for (int i = 0; i < 10; i++){
        P.push_back(i);
    }

    for (int i = 0; i < P.size(); i++){
        std::cout << P.operator[](i) << "\n";
    }

    std::cout << "Размер контейнера: " << P.size() << "\n";

    P.erase(6);
    P.erase(4);
    P.erase(2);

    for (int i = 0; i < P.size(); i++){
        std::cout << P.operator[](i) << "\n";
    }

    P.insert(0, 10);

    for (int i = 0; i < P.size(); i++){
        std::cout << P.operator[](i) << "\n";
    }

    P.insert(P.size()/2, 20);

    for (int i = 0; i < P.size(); i++){
        std::cout << P.operator[](i) << "\n";
    }

    P.push_back(30);

    for (int i = 0; i < P.size(); i++){
        std::cout << P.operator[](i) << "\n";
    }
        */
}
