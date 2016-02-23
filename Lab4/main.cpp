#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	  
#include <cstdio>
#include <cstring>		// для явного определения типов в шаблоне

#define min( a, b ) ((a) < (b) ? (a) : (b))			// пример макроса

// три шага: 
// 1 - поиск кандидатов функций + колличество переменных
// + типы переменных
// 2 - выделение устоявших фунций - по типу и преобразованиям (либо без)
// 3 - Поиск наиболее устойчиво по лучшим преобразованиям или без низ

// общий шаблон
// общий шаблон
template <class Type>
Type minTemplate( Type a, Type b ) { return a < b ? a : b; }
//template<> char minTemplate<char>( char a, char b );
typedef const char *PCC;
template<> PCC minTemplate< PCC >(PCC s1, PCC s2 ) { return "i";}

using namespace std;

// 	объявления функций 
void fun ( int a, 	int b 	 ); 		// 1
void fun ( int a, 	float b  ); 		// 2
void fun ( int a, 	double b ); 		// 3
void fun ( float a, double b ); 		// 4
void fun ( int a, 	int b, double c); 	// 5

//void fun ( int a = 10, int b );  		// ошибка типы данных
//void fun (const int a = 10, int b );  // ошибка так как одинаковые типы
//int fun ( int a = 10, int b );  		// разный тип возврата

int main(int argc, char **argv)
{
	// переменные разных типов
	// для проверки перегрузок
	int intVar = 100, intVar2 = 50;
	float floatVar = 10.5; 
	double doubleVar = 50.5;
	const char *a = "t" , *b = "b"; 
	
	cout << "====Начало====" << endl;
		
	fun(intVar, intVar);			//1
	fun(intVar, floatVar); 			//2
	fun(intVar, doubleVar); 		//3
	fun(floatVar, doubleVar); 		//4
	fun(intVar, intVar, doubleVar); //5
	
	cout << "Пример макроса: " << min (intVar, floatVar) << endl;
	cout << "Пример общего шаблона: " << minTemplate (intVar, intVar2) << endl;
	cout << "Пример специального шаблона: " << minTemplate (a, b) << endl;
	
	return 0;
}

void fun ( int a, 	int b 	 ) { cout << "Функция 1 от int + int" << endl; }
void fun ( int a, 	float b  ) { cout << "Функция 2 от int + float" << endl; }
void fun ( int a, 	double b ) { cout << "Функция 3 от int + double" << endl; }
void fun ( float a, double b ) { cout << "Функция 4 от float + double" << endl; }
void fun ( int a, 	int b, double c) { cout << "Функция 5 от int + int + double" << endl; }
