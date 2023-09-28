#include "car.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

std::vector <std::pair<Car, int>> create_table(int);
bool compareCar(std::pair<Car, int>, std::pair<Car, int>);
int find_fib(int);
int fib(int n);
std::pair <Car, int> fib_search(int, char *);
bool compareChar(char *first, char *second);
bool equalChar(char *first, char *second);

int main() {
    std::cout << "Enter size of file: ";
    int val = 0;
    std::cin >> val;
    std::cout << "Enter number for search: ";
    char* num = new char[7];
    std::cin >> num;
    std::pair <Car, int> res = fib_search(val, num);
    std::cout << res.first.number << ' ' << res.second << '\n';
    return 0;
}

std::vector <std::pair<Car, int>> create_table(int value) {
    std::vector<std::pair<Car, int>> storage;
    storage.resize(value);
    std::ifstream fin("car.bin", std::ios::binary);
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
        storage[i] = {tmp, i};

    }
    for (int i = 0; i < value; ++i) {
        for (int j = i + 1; j < value; ++j) {
            if (compareChar(storage[i].first.number, storage[j].first.number)) {
                std::pair <Car, int> tmp = storage[i];
                storage[i] = storage[j];
                storage[j] = tmp;
            }
        }
    }
    //sort(storage.begin(), storage.end(), compareCar);
    // for (int i = 0; i < value; ++i) {
    //     std::cout << storage[i].first.number << '\n';
    // }
    fin.close();
    return storage;
}

bool compareCar(std::pair<Car, int> i1, std::pair<Car, int> i2)
{
    for (int i = 0; i < 6; ++i) {
        if (i1.first.number[i] < i2.first.number[i]) return true;
        else if (i1.first.number > i2.first.number) return false;
    }
    return (i1.first.number < i2.first.number);
}

bool compareChar(char *first, char *second) {
    for (int i = 0; i < 6; ++i) {
        if (first[i] != second[i]) return (first[i]  > second[i]);
    }
    return false;
}

bool equalChar(char *first, char *second) {
    bool flag = true;
    for (int i = 0; i < 6 && flag; ++i) {
        if (first[i] != second[i]) flag = false;
    }
    return flag;
}

int find_fib(int value) {
    std::vector<int> fib (10000, 1);
    bool flag = true;
    int i;
    for (i = 3; i < 10000 && flag; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] >= value + 1) flag = false;
    }
    return i - 2;
}

int fib(int n) {
    std::vector<int> fib (n, 1);
    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    if (n == 0) return 1;
    return fib[n - 1];
}

std::pair <Car, int> fib_search(int value, char* number) {
    std::vector<std::pair<Car, int>> data = create_table(value);
    std::cout << "sort values:\n";
    for (int i = 0; i < value; ++i) {
        std::cout << data[i].first.number << ' ' << data[i].second << '\n';
    }
    int k = find_fib(value);
    int m = fib(k + 1) - (value + 1);
    int index = fib(k) - m;
    int p = fib(k - 1);
    int q = fib(k - 2);
    std::pair <Car, int> res = {Car(), 0};
    // std::cout << "k = " << k << '\n';
    // std::cout << "m = " << m << '\n';
    std::cout << "index = " << index << '\n';
    // std::cout << "p = " << p << '\n';
    // std::cout << "q = " << q << '\n';
    
    bool flag = true;
    
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
        if(flag && equalChar(number, data[index].first.number)) {
            std::cout << "last " << index << ' ' << data[index].first.number << '\n';
            res = data[index];
            flag = false;
        }
        std::cout << "index = " << index << '\n';
        if (flag && compareChar(number, data[index].first.number) ) { //заменить на компаратор
            std::cout << "second if\n";
            if (q == 0) flag = false;
            else {
                index += q;
                p = p - q;
                q = q - p;
            }
        } else if (flag && !compareChar(number, data[index].first.number)) { //заменить на компаратор
            std::cout << "else if\n";
            if (p == 0) flag = false; // было 1
            else {
                index -= q;
                int tmp = p;
                p = q;
                q = tmp - q;
            }
        }
        if(flag && equalChar(number, data[index].first.number)) {
            std::cout << "last " << index << ' ' << data[index].first.number << '\n';
            res = data[index];
            flag = false;
        }
        std::cout << "loop index: " << index << ' ' << "flag = " << flag << " p= " << p << " q= " << q << '\n';
    }
    std::cout << "end search\n";
    return res;

}