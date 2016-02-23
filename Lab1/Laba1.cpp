#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	 
#include <string> 		// для работы со строками 
#include <fstream>		// для работы с файлами
#include <cstdio>
#include <limits>

using namespace std;

// структуры для друзей
struct Friends
{
    string name;
    string family; 
    int age;
    bool blackList;    
}; 

// считает колличество строк в файле. 
// название фала задается на вход. 
int FileLineCounter (const std::string & strFileName) {
	
	int n = 0; 				// счетчик строк

	ifstream strFile;		// объект файла
	strFile.open (strFileName.c_str(), std::ifstream::in);
	
	char ch;

	for(;;) {
		strFile.get(ch);
		if(strFile.eof()) break;
		if (ch == '\n') {
			n++;
		}
	}
	return n; 
}

void AddFriendsFromFile() { // Добавляем друзей в файл

// вводим колличество друзей
cout << "\n==========Введите колличество ваших друзей\n  " << endl;
int countForFrends = 0; 			// счетчик друзей.  
cin >> countForFrends; 
Friends str[countForFrends]; 		// массив для друзей
cout << "\n==========Введите Имена в формате <Имя> <Фамилия> <Возраст>" << endl; 

// вводим ИМЯ ФАМИЛИЯ ВОЗРАСТ
for (int i = 0; i < countForFrends; i++) {
cin >> str[i].name; 
cin >> str[i].family;
cin >> str[i].age;
}

// проверяем что записалось в массив
cout << "\n==================Давайте проверим" << endl;
for (int i = 0; i < countForFrends; i++) {

cout << str[i].name << " ";
cout << str[i].family << " ";
cout << str[i].age << endl;

}

// вводим название файла
cout << "\n  ============Введите название файла\n  " << endl;
string FileNameStr; 
cin >> FileNameStr; 

// создаём объект для записи в файл
ofstream FriendsFile; // объект класса ofstream
//ofstream ofs(FileNameStr.c_str());// создаем файл
FriendsFile.open(FileNameStr.c_str()); // связываем объект с файлом,
									   // запись в конец файла

cout << "\n===============Записали все в файл" << endl;
for (int i = 0; i < countForFrends; i++) {
FriendsFile << str[i].name << " " 
			<< str[i].family << " " 
			<< str[i].age << endl;
}

FriendsFile.close(); 
}
void WorkWithFile () { // для обработки поступающего файла

// вводим название файла
cout << "\n============Введите название файла\n  " << endl;
string FileNameStr; 
cin >> FileNameStr; 

// открываем файл для чтения
ifstream FriendsFile; 
FriendsFile.open (FileNameStr.c_str(), std::ifstream::in);

// проверяем на открытие 
if ( ! FriendsFile ) {
      cerr << "ошибка: не могу открыть входной файл" << endl;
      return;
   }
cout << "\n==========Читаем файл: " << FileNameStr << endl; 

cout << "\n==========Анализ..." << endl; 
// узнаем сколбко записей в файле
int LineCountInt = FileLineCounter (FileNameStr); // тут костыль
cout << "\n\n В файле " << LineCountInt << " записей\n" <<endl;

// читаем строчки из файла
Friends ArrayForFriends [LineCountInt]; 
for (int i = 0; i < LineCountInt; i++) {
	
	string ageTemp; 
	std::getline(FriendsFile, ArrayForFriends[i].name, ' ');
	std::getline(FriendsFile, ArrayForFriends[i].family, ' ');
	std::getline(FriendsFile, ageTemp, '\n');
	ArrayForFriends[i].age = atoi(ageTemp.c_str());
	
	// фильтруем
	if (ArrayForFriends[i].age < 18) {
	ArrayForFriends[i].blackList = true; // попал в блеклист
	} else ArrayForFriends[i].blackList = false; // не попал
}

// вводим название файла
cout << "\n============Введите название выходного файла\n  " << endl;
cin >> FileNameStr;

// создаём объект для записи в файл
ofstream FriendsFileOutput; // объект класса ofstream
//ofstream ofs(FileNameStr.c_str());// создаем файл
FriendsFileOutput.open(FileNameStr.c_str()); // связываем объект с файлом,
									   // запись в конец файла
for (int i = 0; i < LineCountInt; i++) { // для первых
	if (!ArrayForFriends[i].blackList) { // костыльно
		
		FriendsFileOutput << ArrayForFriends[i].name << " " 
			<< ArrayForFriends[i].family << " " 
			<< ArrayForFriends[i].age << endl;
		
	}
}

for (int i = 0; i < LineCountInt; i++) { // для вторых
	if (ArrayForFriends[i].blackList) { // костыльно
		
		FriendsFileOutput << "blacklist "
						<< ArrayForFriends[i].name << " " 
						<< ArrayForFriends[i].family << " " 
						<< ArrayForFriends[i].age << endl;
		
	}
}


FriendsFile.close(); 
FriendsFileOutput.close (); 
}

void Work () {
	
// вводим название файла
cout << "\n============Введите название файла\n  " << endl;
string FileNameStr; 
cin >> FileNameStr; 

// открываем файл для чтения
fstream FriendsFile; 
FriendsFile.open (FileNameStr.c_str());

// проверяем на открытие 
if ( ! FriendsFile ) {
      cerr << "ошибка: не могу открыть входной файл" << endl;
      return;
   }
cout << "\n==========Читаем файл: " << FileNameStr << endl; 

cout << "==========Анализ..." << endl; 
// узнаем сколбко записей в файле
int LineCountInt = FileLineCounter (FileNameStr); // тут костыль
cout << "\n\nВ файле " << LineCountInt << " записей\n" <<endl;


FriendsFile.seekg(0, FriendsFile.end);
FriendsFile << "============BlackList=========" << endl; 

// идем в начало
FriendsFile.seekg(0, FriendsFile.beg);

// начинаем проверку
Friends FriendsObj; 
for (int i = 0; i < LineCountInt; i++) {
	
	string ageTemp; 
	std::getline(FriendsFile, FriendsObj.name, ' ');
	getline(FriendsFile, FriendsObj.family, ' ');
	getline(FriendsFile, ageTemp, '\n');
	FriendsObj.age = atoi(ageTemp.c_str());
	int length = FriendsFile.tellg();
	
	if (FriendsObj.age <= 18) {
		cout << "Добавляем запись"<< " " << FriendsObj.name << " " << FriendsObj.family << " в черный лист" << endl; 
		FriendsFile.seekg(0, FriendsFile.end);
		FriendsFile << FriendsObj.name << " "  << FriendsObj.family << " " << FriendsObj.age << endl;
        FriendsFile.seekg(length);
		
	}
}		
FriendsFile.close(); 
}


int main() 
{

setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы

while (true) {
cout << "\n==========Наберите 1 для записи в файл" << endl;
cout << "==========         2 для обработки из файла\n  " << endl;

// проверяем ввод
string temp;
cin >> temp;
cin.clear();  // на всякий пожарный подчищаем буфер ввода

if (temp == "1"){ // читаем из файла
	AddFriendsFromFile();
} else if (temp == "2") { // для работы с файлом
	//WorkWithFile(); 
	Work ();	
} else if ((temp != "1") && (temp != "2")) { // не корректный ввод
	cerr << "ошибка: не корректный ввод" << endl;
}
}

return 0; 
}




