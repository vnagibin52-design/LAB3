#include "SContainer.h"
#include "PContainer.h"
#include "OneWaySContainer.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {

    SContainer<int> S;

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

    OneWaySContainer<int> S2;

    for (int i = 0; i < 10; i++){
        S2.push_back(i);
    }

    int i2 = 0;
    for (int value : S2){
        std::cout << value << "\n";
    }

    std::cout << "Размер контейнера: " << S2.size() << "\n";

    auto it2 = S2.begin();
    ++it2;
    ++it2;
    S2.erase(it2.get_node()); 

    ++it2;
    ++it2;    
    S2.erase(it2.get_node()); 

    ++it2;
    ++it2;     
    S2.erase(it2.get_node());

    for (int value : S2){
        std::cout << value << "\n";
    }

    S2.push_front(10);

    for (int value : S2){
        std::cout << value << "\n";
    }

    it2 = S2.begin();
    for(int i = 0; i < S2.size()/2; i++){
        ++it;
    }
    S2.insert(it2.get_node(), 20);

    for (int value : S2){
        std::cout << value << "\n";
    }

    S2.push_back(30);

    for (int value : S2){
        std::cout << value << "\n";
    }

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

    PContainer<int> P2;
    P2 = std::move(P);

    std::cout << "Контейнер P" << "\n";
    for (int i = 0; i < P.size(); i++){
        std::cout << P.operator[](i) << "\n";
    }
    std::cout << "_________________" << "\n";
    std::cout << "Контейнер P2" << "\n";
    for (int i = 0; i < P2.size(); i++){
        std::cout << P2.operator[](i) << "\n";
    }

    } catch (const std::out_of_range& e) {
    std::cerr << "Ошибка: " << e.what() << '\n';
}
}
