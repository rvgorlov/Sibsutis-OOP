#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	  
#include <cstdio>
#include <new>          
#include <fstream>		
#include <string>
#include <fstream>
#include <set>			// Контейнеры
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/* класс объект - функции */
class compare {
	public:
	bool operator ()(const string &s1, const string &s2) { 
		return s1.size() < s2.size();
	}
	bool operator ()(const string &s1) {
		return s1.size() < 6; // Видимо из за кирилицы
	}
};

// Читаем слова из файла в Set
void input_set(set<string> &wordsListSet){
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
		wordsListSet.insert(buf);
	}
	fi.close();
	cout << "\nФайл 1 успешно считан\n" << endl; 
}

// Читаем из второго файла слова которых нет в первом файле
void input_vector(vector<string> &wordsListVector, set<string> &wordsListSet, map<string, int> &statistics){
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
		char notDesiredChars[] = {',', '.', '!', '?', '"', ')', '(', ':', ';', '-'};
		bool check_char_bool = 0; 
		for (int i = 0; i < 10; i++) {
			if (buf.size() == 1 && buf[0] == notDesiredChars[i]) {
					check_char_bool = 1; 
			}
		}
		if (check_char_bool == 1 ) { 
			check_char_bool = 0; 
			continue; 
		}
		// Убиваем невалидные символы в конце строки
		for (int i = 0; i < 10; i++) {
			char tempBack = buf[buf.size() - 1];
			if (notDesiredChars[i] == tempBack) {
				buf.erase(buf.end() - 1);			
			}
		}
		// Проверка на совпадение слов
		if (!wordsListSet.count(buf)) {
			// Добавляем в конец
			wordsListVector.push_back(buf);
		} else {
			// добавляем еденичку для статистики
			statistics[buf]++;
		}
	}
	fi.close();
	cout << "\nФайл 2 успешно считан\n" << endl; 
}

// Сохраняем статистику в файл
void save_statistics(map <string, int> &statistics) {
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

void sort_and_del_repeat_words(vector<string> &wordsListVector) {
	vector<string> :: iterator it1 = wordsListVector.begin();
	vector<string> :: iterator it2 = wordsListVector.end();
	// Сортировка
	sort(it1, it2);
	// Удаление повторений
	it1 = unique(it1, it2);
	wordsListVector.erase(it1, it2);
}

// Стабильная сортировка и удаление коротких строк
void sort_stable_and_del_less_three(vector<string> &wordsListVector) {	
	compare less; 			// Сравнение строк
	compare cmpThree; 		// Сравнение длины 

	vector<string> :: iterator it1 = wordsListVector.begin();
	vector<string> :: iterator it2 = wordsListVector.end();

	stable_sort(it1, it2, less);
	it1 = remove_if(it1, it2, cmpThree);
	wordsListVector.erase(it1, it2);
}

void save_vector(vector <string> &wordsListVector) {
	ofstream fo;
	int i = 0;
	fo.open("vec.txt");
	if (!fo.good()) throw 3;
	for (vector<string> :: iterator it = wordsListVector.begin(); it != wordsListVector.end(); it++) {
			fo << (*it) << endl;
			i++;
	}
	fo.close();
}

int main(int argc, char **argv){
	try { 
		// Создаем переменные для хранения файлов
		set<string> wordsListSet;
		vector<string> wordsListVector;
		map<string, int> statistics;
		// Считываем файлы со словами
		input_set(wordsListSet);
		input_vector(wordsListVector, wordsListSet, statistics);
		
		// сохраняем статистику повторяющихся слов в двух файлах
		save_statistics(statistics);
		
		// Удаляем повторы, сортируем лексиграфически
		sort_and_del_repeat_words(wordsListVector);
		sort_stable_and_del_less_three(wordsListVector);
		
		save_vector(wordsListVector); 
		
	}
	catch (int a) {
		if (a == 1) cout << "Нет файла для создания SET" << endl;
		else if (a == 2) cout << "Нет файла для создания VECTOR" << endl;
		else if (a == 3) cout << "Не создается файл" << endl;
		else if (a == 4) cout << "Не создается файл для статистики" << endl;
	}
	return 0;
}

