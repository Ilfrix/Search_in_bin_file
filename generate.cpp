#include <iostream>
#include <fstream>
#include <set>
#include <ctime>
#include "car.h"

using namespace std;

void input(int);

int main() {
    int value = 0;
    cout << "Enter value: ";
    cin >> value;
    input(value);
    return 0;
}
void input(int value) {
    ofstream fout("car.bin", ios::binary);
    ofstream file_out("car.txt");
    set<string> check;
    srand(time(nullptr));
    char inf[6][13] = {{"Rich_guy"}, {"Poor_guy"}, {"Has_children"}, {"Single"}, {"Unemployed"}, {"Businessman"}};
    int inf_size[] = {9, 9, 13, 7, 11, 12};
    char marks[12][12] = {{"Audi"}, {"BMW"}, {"Lada"}, {"Kamaz"}, {"Reno"}, {"Chevrolet"}, {"Toyota"}, {"Ford"}, {"Mazda"}, {"Volkswagen"}, {"Kia"}, {"Nissan"}};
    int marks_size[] = {5, 4, 5, 6, 5, 10, 7, 5, 6, 11, 4, 7};
    Car automobile[value];
    for (int i = 0; i < value; ++i) {
        char first  = char('a' + rand() % 26);
        char second = char('a' + rand() % 26);
        char third  = char('a' + rand() % 26);
        char* name_car = new char[6];
        string k = to_string(rand() % 1000);
        while (k.size() < 3) k = '0' + k;
        name_car[0] = first;
        name_car[1] = second;
        name_car[2] = k[0];
        name_car[3] = k[1];
        name_car[4] = k[2];
        name_car[5] = third;
        if (check.find(name_car) != check.end()) --i;
        else{
            check.insert(name_car);
            int m_size = rand() % 12;
            int i_size = rand() % 6;
            char* mark = marks[m_size];
            char* info = inf[i_size];
            int number_val = 6;
            int mark_val = marks_size[m_size];
            int info_val = inf_size[i_size];
            
            fout.write((char *) &number_val, sizeof(int));
            fout.write((char *) &mark_val, sizeof(int));
            fout.write((char *) &info_val, sizeof(int));
            fout.write((char *) name_car, number_val);
            fout.write((char *) mark, mark_val);
            fout.write((char *) info, info_val);
            file_out << number_val << ' ' << mark_val << ' ' << info_val << '\t' << name_car << ' ' << mark << ' ' << info << '\n';
        }
    }
    fout.close();
    file_out.close();
}