#include <iostream>
#include <vector>
#include <list>


int main() {

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
        }
}
