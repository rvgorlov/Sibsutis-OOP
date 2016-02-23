#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	  
#include <cstdio>
#include <new>          
#include <fstream>		
#include <string>
#include <set>			// Контейнеры
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Класс объект - функции
class compare {
	public:
	bool operator ()(const string &s1, const string &s2) { 
		return s1.size() < s2.size();
	}
	bool operator ()(const string &s1) {
		return s1.size() < 3; 
	}
};

// Читаем слова из файла в Set
void input_set(set<string> &WordSet){
	ifstream fi;
	fi.open("set.txt");
	if (!fi.good()) {
		// Если нет файла
		throw 1;
	}
	while (1) {
		string buf;
		getline(fi, buf);
		if (fi.eof()) break;
		WordSet.insert(buf);
	}
	fi.close();
	cout << "\nФайл 1 успешно считан\n" << endl; 
}

// Читаем из второго файла слова которых нет в первом файле
void input_vector(vector<string> &WordVect, set<string> &WordSet, map<string, int> &statistics){
	ifstream fi;
	fi.open("vector.txt");
	if (!fi.good()) {
		// Если нет файла
		throw 2;
	}
	while (!fi.eof()) {
		string buf;
		getline(fi, buf, ' ');
		// Проверка невалидных символов
		char notDesiredChars[] = {',', '.', '!', '?', '"', ')', '(', ':', ';', '-', '\n'};
		bool check_char_bool = 0; 
		for (int i = 0; i < 11; i++) {
			if (buf.size() == 1 && buf[0] == notDesiredChars[i]) {
					check_char_bool = 1; 
			}
		}
		if (check_char_bool == 1 ) { 
			check_char_bool = 0; 
			continue; 
		}
		// Убиваем невалидные символы в конце строки
		for (int i = 0; i < 11; i++) {
			char tempBack = buf[buf.size() - 1];
			if (notDesiredChars[i] == tempBack) {
				buf.erase(buf.end() - 1);			
			}
		}
		// Проверка на совпадение слов
		if (!WordSet.count(buf) && !WordSet.count("")) {
			// Добавляем в конец
			WordVect.push_back(buf);
		} else {
			// добавляем еденичку для статистики
			statistics[buf]++;
		}
	}
	fi.close();
	cout << "\nФайл 2 успешно считан\n" << endl; 
}

// Сохраняем статистику в файл
void Print_stat(map <string, int> &statistics) {
	int i = 0;
	ofstream fo;
	fo.open("stat.txt");
	if (!fo.good()) throw 4;
	for (map<string, int> :: iterator it = statistics.begin(); it != statistics.end(); it++) {
		if((*it).second > 1) {
			fo << (*it).first << endl << (*it).second << endl;
			i++;
		}
	}
	fo.close();
	cout << "\nСтатистика успешно записана\n" << endl; 
}

void SortVec_DelRep(vector<string> &WordVect) {
	vector<string> :: iterator it1 = WordVect.begin();
	vector<string> :: iterator it2 = WordVect.end();
	// Сортировка
	sort(it1, it2);
	// Удаление повторений
	it1 = unique(it1, it2);
	WordVect.erase(it1, it2);
	cout << "\nОтсортировали массив и удалили повторения\n" << endl; 
}

// Стабильная сортировка и удаление коротких строк
void SortVec_DelRep_stable(vector<string> &WordVect) {	
	compare less; 			// Сравнение строк
	compare cmpThree; 		// Сравнение длины 

	vector<string> :: iterator it1 = WordVect.begin();
	vector<string> :: iterator it2 = WordVect.end();

	stable_sort(it1, it2, less);
	it1 = remove_if(it1, it2, cmpThree);
	WordVect.erase(it1, it2);
	cout << "\nСтабильно отсортировали и удалили короткие слова\n" << endl; 
}

void save_vector(vector <string> &WordVect) {
	ofstream fo;
	fo.open("vec.txt");
	if (!fo.good()) throw 3;
	for (vector<string> :: iterator it = WordVect.begin(); it != WordVect.end(); it++) {
			fo << (*it) << endl;
	}
	fo.close();
	cout << "\nЗаписали результат в файл\n" << endl; 
}

int main(int argc, char **argv){
	try { 
		// Создаем переменные для хранения файлов
		set<string> WordSet;
		vector<string> WordVect;
		map<string, int> statistics;
		// Считываем файлы со словами
		input_set(WordSet);
		input_vector(WordVect, WordSet, statistics);
		
		// сохраняем статистику повторяющихся слов в двух файлах
		Print_stat(statistics);
		
		// Удаляем повторы, сортируем лексиграфически
		SortVec_DelRep(WordVect);
		SortVec_DelRep_stable(WordVect);
		
		save_vector(WordVect); 
		
	}
	catch (int a) {
		if (a == 1) cout << "Нет файла для создания SET" << endl;
		else if (a == 2) cout << "Нет файла для создания VECTOR" << endl;
		else if (a == 3) cout << "Не создается файл" << endl;
		else if (a == 4) cout << "Не создается файл для статистики" << endl;
	}
	return 0;
}

