#include <iostream>		// Ввод вывод
#include <fstream>		// Для файловых потоков
#include <iterator>		// Итераторы
#include <vector>		// Контейнейр вектор
#include <map>			// Контейнер мэп
#include <algorithm>	// Для обработки контейнеров
#include <string>		// Для работы со строками
#include <cstdlib>		// Выделение памяти, контроль итд. 
#include <utility>		// Для создания pair
#include <sstream>		// Ввод вывод в строку 

using namespace std;

// Контейнеры для словаря и текста
vector<string> simpleText;				// Контейнер текста
map<string, string> dictionary;			// Контейнер словаря
char *tmpForFile;   

// Для считывания словаря 
struct istream_pair :public pair<string, string>
{};

// Перегрузка оператора ввода
template <
	typename CharT, 
	typename Traits>
basic_istream<CharT, Traits>&  operator >> (basic_istream<CharT, Traits> &in,
											istream_pair &value)
{
    in >> value.first;
    in >> value.second;
    return in;
}

// Объявляем функции
void StudentName ();
void ReadText(vector<string> &simpleText);
void ReadDict(map<string, string> &Dictionary); 
void CheckVector(string &s);
void SaveVector(vector<string> &vector);
void SaveVector(vector<char> &vector);  		

int main(int argc, char **argv)
{
	StudentName(); 
	// Читаем простой текст из первого файла
	ReadText(simpleText);
	// Читаем словарь из второго файла
	ReadDict(dictionary);
	// Обрабатывем входной массив согласно заданию
	for_each(simpleText.begin(), simpleText.end(), CheckVector);
	SaveVector(simpleText); 
	
	return 0;
}

// Читаем из файла словарь
void ReadDict(map<string, string> &Dictionary)
{
 	char FileName[256];				// Название файла
	ifstream fileDict;				// файл
	bool io_flag;					// флаг состояния файла
 	
	do {
		cout << "Введите название файла словаря: "; 
		cin >> FileName; 
		io_flag = 0;
		ifstream fileDict(FileName);
		if (!fileDict.good()) {
			cout << "~ Нет такого файла\n";
			io_flag = 1;
		} else {
			cout << "~ Файл найден\n";
			map<string, string> mapTemp(
				(istream_iterator<istream_pair>(fileDict)), 
				istream_iterator<istream_pair>()
			);
			Dictionary = mapTemp;
			fileDict.close();
		} 
	} while (io_flag == 1);
	
}

// Проверка темпа
void CheckStr(
	vector<string> &simpleText,
	string str = ""
	)
{
	if (!str.empty())
		simpleText.push_back(str);	
}

 //Перевод из char в string
void SymbolsToWord(	
	vector<char> &tempChar, 
	vector<string> &simpleText, 
	unsigned long int &idx,
	string &tempWord
	) 
{
	//Добавляем новый символ в строку 
	if ( tempChar[idx] != ' '  &&
		 tempChar[idx] != '\n' &&
		 tempChar[idx] != '\t' &&
		 tempChar[idx] != '.' &&
		 tempChar[idx] != ',' ) 
	{
		tempWord.push_back(tempChar[idx]); 
	} 
	if ( tempChar[idx] == ' ')
	{
		//simpleText.push_back ( tempWord ); 
		CheckStr(simpleText, tempWord); 
		tempWord.clear();
		simpleText.push_back ( " " );
	} 
	else if (tempChar[idx] == '\n') {
		CheckStr(simpleText, tempWord); 
		tempWord.clear();
		simpleText.push_back ( "\n" );
	} 
	else if (tempChar[idx] == '\t') {
		CheckStr(simpleText, tempWord); 
		tempWord.clear();
		simpleText.push_back ( "\t" );
	}
	else if (tempChar[idx] == ',') {
		CheckStr(simpleText, tempWord); 
		tempWord.clear();
		simpleText.push_back ( "," );
	}
	else if (tempChar[idx] == '.') {
		CheckStr(simpleText, tempWord); 
		tempWord.clear();
		simpleText.push_back ( "." );
	}
	
	idx++;
	// Продбегаем по всему вектору
	if ( idx != tempChar.size() )  
		SymbolsToWord (tempChar, simpleText, idx , tempWord);

} 

// Читаем простой текст из файла
void ReadText( vector <string> &simpleText){
	
	vector<char> tempChar; 
	char FileName[256];				// Название файла
	ifstream fileText;				// файл
	bool io_flag = 0;				// флаг состояния файла
	do {
		cout << "Введите название файла c простым текстом: "; 
		cin >> FileName; 
		io_flag = 0;
		ifstream fileText(FileName);
		if (!fileText.good()) {
			cout << "~ Нет такого файла\n";
			io_flag = 1;
		} else {
			cout << "~ Файл найден\n";
			// Читаем из файла в вектор посимвольно
			copy (
				istreambuf_iterator<char>(fileText),
				istreambuf_iterator<char>(),
				back_inserter(tempChar));
			// Тестовое сохранение
			unsigned long int idx = 0; 
			string tempStr = ""; 
			SymbolsToWord(tempChar, simpleText, idx, tempStr);
			fileText.close();
		}	 
	} while (io_flag == 1);
	
}

void CheckVector(string &s)
{
	map <string, string> :: iterator it;
	string tmpString(s);
	it = dictionary.find(tmpString);
	
	if (it != dictionary.end()) {
		s = (*it).second; 
	}
}

// Для теста
void SaveVector(vector<char> &vector)
{
	char FileName[256];				// Название файла
	cout << "Введите название файла для результата: "; 
	cin >> FileName;
	ofstream fileResult(FileName);
	copy(vector.begin(), vector.end(), ostream_iterator<char>(fileResult, ""));
	fileResult.close();
	cout << "~ Файл сохранен\n";
}
void SaveVector(vector<string> &vector)
{
	char FileName[256];				// Название файла
	cout << "Введите название файла для результата: "; 
	cin >> FileName;
	ofstream fileResult(FileName);
	copy(vector.begin(), vector.end(), ostream_iterator<string>(fileResult, ""));
	fileResult.close();
	cout << "~ Итого слов: " << vector.size() << endl; 
	cout << "~ Файл сохранен\n";
}

// Индентификатор студента
void StudentName () {
	cout 	<< "\t##################\n"
			<< "\t#Лабораторная №6 #\n"
			<< "\t#Горлова Романа  #\n"
			<< "\t#ИУ-423          #\n"
			<< "\t##################\n"
			<< endl; 
}
