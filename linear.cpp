#include "car.h"
#include <fstream>
#include <chrono>
#include <iostream>

Car find_linear(std::string, int);

int main() {
    int value = 0;
    std::string num = "";
    std::cout << "Enter size of file: ";
    std::cin >> value;
    std::cout << "Enter number of car: ";
    std::cin >> num;

    Car res = find_linear(num, value);
    std::cout << res.mark << ' ' << res.info << '\n'; 
    return 0;
}

Car find_linear(std::string num, int value) {
    // 100 - 997
    // 1000 - 3007
    // 10000 - 13012
    std::ifstream fin("car.bin", std::ios::binary);
    Car search[value];
    
    int index = -1;
    bool flag = true;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < value && flag; ++i) {
        Car tmp;

        fin.read((char *) &tmp.number_val, sizeof(int));
        fin.read((char *) &tmp.mark_val, sizeof(int));
        fin.read((char *) &tmp.info_val, sizeof(int));

        tmp.number = new char[tmp.number_val];
        tmp.mark = new char[tmp.mark_val];
        tmp.info = new char[tmp.info_val];

        fin.read((char *)tmp.number, tmp.number_val);
        fin.read((char *)tmp.mark, tmp.mark_val);
        fin.read((char *)tmp.info, tmp.info_val);
        search[i] = tmp;
        // std::cout << tmp.number_val << ' ' << tmp.mark_val << ' ' << tmp.info_val << '\t' << tmp.number << ' ' << tmp.mark << ' ' << tmp.info << '\n';
        if (search[i].number == num) {
            flag = false;
            index = i;
        }
        delete[] tmp.number;
        delete[] tmp.mark;
        delete[] tmp.info;
    }
    if (flag) {
        index = 0;
        Car tmp = Car();
        tmp.number = nullptr;
        tmp.mark = nullptr;
        tmp.info = nullptr;
        search[0] = tmp;
    }
    fin.close();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << " time: " << duration.count() << '\n';
    return search[index];
}