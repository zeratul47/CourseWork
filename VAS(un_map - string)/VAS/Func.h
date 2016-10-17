#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map <string, int>::iterator iter;
//функция P
double P(int kt, int kf, int a, int b);

//примитивный факториал
int fact(int x);

//создание матрицы последовательностей (T и F)
vector<string> CreateSet(char* name, int & t);

//подсчет kf
int NumberKF(string P, vector<string> & F, const int f);

//перебор сочетаний из l по d
vector<vector<int>> CreateSubIndex(const int d, const int l);

//делаем D замен (вставляем сразу в хеш таблицу все возможно подстроки длины l со всеми возможными D заменами)
//функция не срабатывает при D = 0 и D = l
void SubStrL(const string &str, vector<int> & SubIndex, unordered_map <string, int> &V);

//функция сравнение для сортировки
bool Comp(iter t1, iter t2);

#endif //FUNC_H