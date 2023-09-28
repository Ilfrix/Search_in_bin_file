#include "car.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>

std::vector <std::pair<char*, int>> create_table(int);
int find_fib(int);
int fib(int n);
std::pair <char*, int> fib_search(int, char *);
bool compareChar(char *first, char *second);
bool equalChar(char *first, char *second);
Car read_bin(int);

int main() {
    std::cout << "Enter size of file: ";
    int val = 0;
    std::cin >> val;
    std::cout << "Enter number for search: ";
    char* num = new char[7];
    std::cin >> num;

    std::pair <char *, int> res = fib_search(val, num);
    std::cout << res.first << ' ' << res.second << '\n';
    Car new_car =  read_bin(res.second);
    std::cout << "Car: " << new_car.number << ' ' << new_car.mark << ' ' << new_car.info << '\n';
    delete[] new_car.number;
    delete[] new_car.mark;
    delete[] new_car.info;
    delete[] res.first;
    return 0;
}

std::vector <std::pair<char*, int>> create_table(int value) { // read data and sort
    std::vector<std::pair<char*, int>> storage;
    storage.resize(value);
    std::ifstream fin("car.bin", std::ios::binary);
    int cur = 0, last = 0;

    for (int i = 0; i < value; ++i) {
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
        cur += last;
        storage[i] = {tmp.number, cur};
        
        // delete[] tmp.number;
        delete[] tmp.mark;
        delete[] tmp.info;
        
        last = tmp.number_val + tmp.mark_val + tmp.info_val + 3 * sizeof(int);
    }

    for (int i = 0; i < value; ++i) {
        for (int j = i + 1; j < value; ++j) {
            if (compareChar(storage[i].first, storage[j].first)) {
                std::pair <char*, int> tmp = storage[i];
                storage[i] = storage[j];
                storage[j] = tmp;
            }
        }
    }
    
    fin.close();
    return storage;
}

bool compareChar(char *first, char *second) { // compare two char * valuables
    for (int i = 0; i < 6; ++i) {
        if (first[i] != second[i]) return (first[i]  > second[i]);
    }
    return false;
}

bool equalChar(char *first, char *second) { // compare of eauals two char * variables
    bool flag = true;
    for (int i = 0; i < 6 && flag; ++i) {
        if (first[i] != second[i]) flag = false;
    }
    return flag;
}

int find_fib(int value) { // find k for fibonacci
    std::vector<int> fib (10000, 1);
    bool flag = true;
    int i = 0;

    for (i = 3; i < 10000 && flag; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] >= value + 1) flag = false;
    }
    return i - 2;
}

int fib(int n) { // simple fibbonacci's values
    std::vector<int> fib (n, 1);
    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    if (n == 0) return 1;
    return fib[n - 1];
}

std::pair <char*, int> fib_search(int value, char* number) { // search of fibonacci
    // 100 - 1
    // 1000 - 4
    // 10000 - 6
    std::vector<std::pair<char *, int>> data = create_table(value);
    int k = find_fib(value);
    int m = fib(k + 1) - (value + 1);
    int index = fib(k) - m;
    int p = fib(k - 1);
    int q = fib(k - 2);
    bool flag = true;
    std::pair <char*, int> res = {nullptr, 0};
    
    auto start = std::chrono::high_resolution_clock::now();
    while (flag) {
        if (index < 0) {
            if (q == 0) flag = false;
            else {
                index += q;
                p = p - q;
                q = q - p;
            }
        } else if (index >= value) {
            if (p == 1) flag = false;
            else {
                index -= q;
                int tmp = p;
                p = q;
                q = tmp - q;
            }
        }
        if(flag && index >= 0 && index < value && equalChar(number, data[index].first)) {
            res = data[index];
            flag = false;
        }

        if (flag && index >= 0 && index < value && compareChar(number, data[index].first) ) {
            if (q == 0) flag = false;
            else {
                index += q;
                p = p - q;
                q = q - p;
            }
        } else if (flag && index >= 0 && index < value && !compareChar(number, data[index].first)) { 
            if (p == 0) flag = false; 
            else {
                index -= q;
                int tmp = p;
                p = q;
                q = tmp - q;
            }
        }
        if(flag && index >= 0 && index < value && equalChar(number, data[index].first)) {
            res = data[index];
            flag = false;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << " time: " << duration.count() << '\n';
    for (int i = 0; i < data.size(); ++i) {
        if (i != index) delete[] data[i].first;
    }
    return res;
}

Car read_bin(int value) {
    Car result;
    std::ifstream fin("car.bin", std::ios::binary);
    fin.seekg(value , std::ios::beg);
    fin.read((char *) &result.number_val, sizeof(int));
    fin.read((char *) &result.mark_val, sizeof(int));
    fin.read((char *) &result.info_val, sizeof(int));

    result.number = new char[result.number_val];
    result.mark = new char[result.mark_val];
    result.info = new char[result.info_val];

    fin.read((char *) result.number, result.number_val);
    fin.read((char *) result.mark, result.mark_val);
    fin.read((char *) result.info, result.info_val);

    fin.close();
    return result;
}