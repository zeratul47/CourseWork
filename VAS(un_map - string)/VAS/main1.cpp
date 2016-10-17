#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include "Func.h"
#include <ctime>
#include <fstream>

using namespace std;

unordered_map <string, int> V;

int main(int argc, char ** argv){
	string inpT = argv[1];
	string inpF = argv[2];
	int l = atoi(argv[3]);

	string motif, motif1;
	vector<string> T;
	vector<string> F;

	int t, f, n; 
	/* l - длина подстроки S; 
	t, f - количества последовательностей длины n в T и F;*/
	
	cout << "Enter the length of sub string S (l) " << l << endl;
	//cin >> l;

	double start = clock();		//для измерения времени

	T = CreateSet("T.txt", t);
	F = CreateSet("F.txt", f);
	n = T.at(0).size();

	vector<vector<vector<int>>> indexs (l);
	string dlPs;
	for (int i = 0; i < l; ++i){
		indexs[i] = CreateSubIndex(i, l);								//создаем масив индексов для замен (каждый подмассив - набор индексов для 1-й строки, в которой будет замена)
		dlPs.push_back('N');
	}
	
	//первая часть алгоритма
	for (int i = 0; i < t; ++i){
		for(int g = 0; g < (n - l + 1); ++g){
			for (int d = 0; d <= l; ++d){
				if (d != l){											//если у нас количество замен = l, то наша строка имеет вид NNNN, где кол-во N равно l
					if (d != 0)
						for (size_t j = 0; j < indexs[d].size(); ++j){				
							SubStrL(T[i].substr(g, l), indexs[d][j], V);				//создаем все возможные строки со все возможными заменами в позициях записаных в index[j]
						}
					else
						++(V[T[i].substr(g, l)]);				//если кол-во замен = 0, то вставляем выделенную подстроку
				}
				else
					++(V[dlPs]);							//добавление NNNN
			}
		}
	}

	//сортировка
	vector<iter> SortValue (V.size());
	int it = 0;			
	iter iterV;			//итератор хеш-таблицы
	for (iterV = V.begin(); iterV != V.end(); iterV++){
		SortValue[it] = iterV;
		++it;
	}
	std::sort(SortValue.begin(), SortValue.end(), Comp);
	
	//вторая часть алгоритма
	string out = "output.txt";
	ofstream fout (out);
	double minp = 1;								//min p-value
	int a = t*(n-l+1);
	int b = f*(n-l+1);
	int kt, kf;												// kt, kf - количество вариантов P в T  и F  соответсвенно
	for (size_t i = 0; i < SortValue.size(); ++i){
		kt = SortValue[i]->second;
		if (P(kt, 0, a, b) < minp) {
			kf = NumberKF(SortValue[i]->first, F, f);
			if (P(kt, kf, a, b)  < minp){
				minp = P(kt, kf, a, b);
				motif = SortValue[i]->first;	
			}
		}
		else {
			if((motif.size() != 0) && (motif1 != motif)){
				motif1 = motif;
				fout << ">Motif" << endl;
				fout << motif << endl;
			}
		}
	}
	if(motif.size() == 0)
		fout << "Motif not found" << endl;

	cout << "see file: '" << out << "'"<< endl;
	cout << "alg" << endl;
	printf("%.4lf\n", (clock() - start) / CLOCKS_PER_SEC);
	fout.close();
	system("pause");
	return 0;
}