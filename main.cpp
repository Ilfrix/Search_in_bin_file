#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>


#define MAX_VAL 10

using namespace std;


vector <pair<Car, int>> create_table();
bool compareCar(pair<Car, int>, pair<Car, int>);
int find_fib();
pair <Car, int> fib_search(string);

int main() {

    return 0;
}

bool compareCar(pair<Car, int> i1, pair<Car, int> i2)
{
    return (i1.first.number < i2.first.number);
}

vector <pair<Car, int>> create_table() {
    vector<pair<Car, int>> storage;
    storage.resize(MAX_VAL);
    ifstream fin("car.txt", ios :: binary);
    Car tmp[MAX_VAL];
    for (int i = 0; i < MAX_VAL; ++i) {
        fin.read((char *) &tmp[i], sizeof(Car));
        storage[i] = {tmp[i], i};
    }
    for (int i = 0; i < MAX_VAL; ++i) {
        cout << storage[i].first.number << ' ' << storage[i].second << '\n';
    }
    sort(storage.begin(), storage.end(), compareCar);
    return storage;
}

int find_fib() {
    vector<int> fib {10000, 1};
    bool flag = true;
    int i;
    for (i = 2; i < 10000 && flag; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] >= MAX_VAL + 1) flag = false;
    }
    return i - 1;
}

int fib(int n) {
    vector<int> fib {n, 1};
    for (int i = 2; i < n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n - 1];
}

pair <Car, int> fib_search(string number) {
    vector<pair<Car, int>> data = create_table();
    int k = find_fib();
    int m = fib(k + 1) - (MAX_VAL + 1);
    int index = fib(k) - m;
    int p = fib(k - 1);
    int q = fib(k - 2);
    bool flag = true;
    pair <Car, int> res = {Car(), 0};
    while (flag) {
        if (index < 0) {
            if (q == 0) flag = false;
            else {
                index += q;
                p = p - q;
                q = q - p;
            }
        } else if (index >= MAX_VAL) {
            if (p == 1) flag = false;
            else {
                index -= q;
                p = q;
                int tmp = p;
                q = tmp - q;
            }
        }
        if (flag && number < data[index].first.number) {
            if (q == 0) flag = false;
            else {
                index += q;
                p = p - q;
                q = q - p;
            }
        } else if (flag && number > data[index].first.number) {
            if (p == 1) flag = false;
            else {
                index -= q;
                p = q;
                int tmp = p;
                q = tmp - q;
            }
        } else if(flag){
            res = data[index];
            flag = false;
        }
    }
    return res;

}