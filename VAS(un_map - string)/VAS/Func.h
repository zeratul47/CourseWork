#ifndef FUNC_H
#define FUNC_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map <string, int>::iterator iter;
//������� P
double P(int kt, int kf, int a, int b);

//����������� ���������
int fact(int x);

//�������� ������� ������������������� (T � F)
vector<string> CreateSet(char* name, int & t);

//������� kf
int NumberKF(string P, vector<string> & F, const int f);

//������� ��������� �� l �� d
vector<vector<int>> CreateSubIndex(const int d, const int l);

//������ D ����� (��������� ����� � ��� ������� ��� �������� ��������� ����� l �� ����� ���������� D ��������)
//������� �� ����������� ��� D = 0 � D = l
void SubStrL(const string &str, vector<int> & SubIndex, unordered_map <string, int> &V);

//������� ��������� ��� ����������
bool Comp(iter t1, iter t2);

#endif //FUNC_H