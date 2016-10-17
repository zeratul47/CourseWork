#include <iostream>
#include <fstream>
#include "Func.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//примитивный факториал
int fact(int x){
    if(x == 0)
       return 1;
    else
       return x*fact(x-1);
}

//функци€ P
double P(int kt, int kf, int a, int b){
	int min;
	double	s, c1,c2, c3;
	s = 0;
	c1 = 1;
	c2 = 1;
	c3 = 1;
	(a+b) < (kt + kf) ? min = a+b : min = kt + kf; 
	for (int ktt = kt; ktt <= min; ++ktt){
		/*
		такой расчет € использовал потому что, если считать в лоб факториалы, то возникает переполнение пам€ти.
		“.к. часть элементов все равно сокращаетс€ € использую if.
		*/
		//расчет c1
		if (kt < a-kt){													
			for(int i = a; i > a-kt ; --i){
				c1 *= i;
			}
			for(int i = 1; i <= kt; ++i){
				c1 /= i;
			}
		}
		else{
			for(int i = a; i > kt ; --i){
				c1 *= i;
			}
			for(int i = 1; i <= a-kt; ++i){
				c1 /= i;
			}
		}

		//расчет c2
		if (kf < b - kf){
			for(int i = b; i > b-kf ; --i){
				c2 *= i;
			}
			for(int i = 1; i <= kf; ++i){
				c2 /= i;
			}
		}
		else{
			for(int i = b; i > kf ; --i){
				c2 *= i;
			}
			for(int i = 1; i <= b- kf; ++i){
				c2 /= i;
			}
		}


		//расчет с3
		if (a + b - kt - kf > kt+kf){
			for(int i = a + b; i > a + b - kt - kf; --i){
				c3 *= i;
			}
			for(int i = 1; i <= kt+kf; ++i){
				c3 /= i;
			}
		}
		else{
			for(int i = a + b; i > kt+kf; --i){
				c3 *= i;
			}
			for(int i = 1; i <= a + b - kt - kf; ++i){
				c3 /= i;
			}
		}
		s = s + c1*c2/c3;
	}
	return s;
}


//создание матрицы последовательностей (T и F) (чтение из формата FASTA)
vector<string> CreateSet(char* name, int & t){
	
	ifstream fin(name);
	string tt;
	vector<string> setGen;
	getline(fin, tt);
    while(fin){
		while(tt[0] != '>' && fin)
			getline(fin, tt);
		getline(fin, tt);
		setGen.push_back (tt);
    }
	fin.close();
	t = setGen.size() -1;
    return setGen;    
}

//делаем D замен (вставл€ем сразу в хеш таблицу все возможно подстроки длины l со всеми возможными D заменами)
//функци€ не срабатывает при D = 0 и D = l
void SubStrL(const string &str, vector<int> & SubIndex, unordered_map <string, int> &V){
	string temp = str;
	
	//делаем D замен
	for(size_t i = 0; i < SubIndex.size(); ++i){
		temp[SubIndex[i]] = 'N';
	}
	++V[temp];
	return;
}

//подсчет kf
int NumberKF(string P, vector<string> & F, const int f){
	int kf =0;
	int Ps = P.size();
	int FiS = F[0].size();
	for(int i = 0; i < f; ++i){					//обход по всем строкам
		for(int j = 0; j < FiS - Ps +1; ++j){		//по всем подстрокам длины l
			bool b = true;
			for(int g = 0; g < Ps; ++g){						//проверка входжени€
				if ((P[g] != F[i][j+g]) && (P[g] != 'N')){
					b = false;
					break;
				}
			}
			if (b) {++kf;}			//если да то увеличиваем kf
		}
	}
	return kf;
}

//перебор сочетаний из l по d
vector<vector<int>> CreateSubIndex(const int d, const int l){
	vector<vector<int>> index;
	vector<int> temp;
	if (d == 0) 
		return index;
	int n = l;
	int k = d;
	int m, i;
	vector<int> A;

	k = k - 1;
	for (i = 0; i <= k; ++ i){
		A.push_back(i);
	}
	int p = k;

	while (p >= 0){
		for (m = 0; m <= k; ++m){
			temp.push_back(A[m]);
		}
		index.push_back(temp);
		temp.clear();

		if (A[k] == n - 1)
			p = p - 1;
		else
			p = k;

		if (p >= 0)
			for (i = k; i >= p; --i)
				A[i] = A[p] + i - p + 1;
	}
	return index;
}

//функци€ сравнение дл€ сортировки
bool Comp(iter t1, iter t2){
	return (t1->second > t2->second);
}